#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

struct UnionFind {
	vector<int> par, siz;

	UnionFind(int n) : par(n, -1), siz(n, 1) {}

	int root(int x) {
		if (par[x] == -1) return x;
		else return root(par[x]);
	}

	bool unite(int x, int y) {
		x = root(x), y = root(y);
		if (x == y) return false;
		if (siz[x] < siz[y]) swap(x, y);
		siz[x] += siz[y];
		par[y] = x;
		return true;
	}
};

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);

	int n, m, answer = 0;
	cin >> n >> m;

	UnionFind uf(n);
	for (int i = 1; i <= m; ++i) {
		int a, b;
		cin >> a >> b;
		bool chk = uf.unite(a, b);
		if (!chk && answer == 0) answer = i;
	}
	if (answer == 0) cout << 0;
	else cout << answer;
	return 0;
}