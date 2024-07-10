#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>
#include<algorithm>

using std::swap;
using std::make_pair;
using std::string;
using std::cin;
using std::cout;
using std::vector;
using std::unordered_map;

struct UnionFind {
	unordered_map<string, int> match;
	vector<int> par, siz;

	UnionFind(int n) : par(n, -1), siz(n, 1) {}

	int root(int x) {
		if (par[x] == -1) return x;
		else return root(par[x]);
	}

	bool issame(int x, int y) {
		x = root(x), y = root(y);
		return x == y;
	}

	bool unite(int x, int y) {
		x = root(x), y = root(y);
		if (x == y) return false;
		if (siz[x] < siz[y]) swap(x, y);
		siz[x] += siz[y];
		par[y] = x;
		return true;
	}

	int get_size(int x) {
		x = root(x);
		return siz[x];
	}

};

int main() {
	cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	int T, F;
	string A, B;
	cin >> T;
	for (int i = 0; i < T; ++i) {
		UnionFind uf(200001);
		cin >> F;
		int index = 0;
		for (int j = 0; j < F; ++j) {
			cin >> A >> B;
			if (uf.match.find(A) == uf.match.end()) uf.match.insert(make_pair(A, index++));
			if (uf.match.find(B) == uf.match.end()) uf.match.insert(make_pair(B, index++));
			uf.unite(uf.match[A], uf.match[B]);
			cout << uf.get_size(uf.match[A]) << "\n";
		}
	}
	return 0;
}