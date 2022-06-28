#include<iostream>
#include<vector>
#include<algorithm>

using std::cin;
using std::cout;
using std::vector;
using std::swap;

struct UnionFind {
	vector<int> par, siz;

	UnionFind(int n) : par(n, -1), siz(n, 1) {}

	int root(int x) {
		if (par[x] == -1) return x;
		else return root(par[x]);
	}
	bool is_same(int x, int y) {
		x = root(x), y = root(y);
		return x == y;
	}
	bool unite(int x,int y) {
		x = root(x), y = root(y);
		if (x == y) return false;
		if (siz[x] < siz[y]) swap(x, y); // x > y 되도록
		par[y] = x;
		siz[x] += siz[y];
		return true;
	}
};

int main() {
	cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	int n, m;
	cin >> n >> m;
	UnionFind uf(n + 1); // 0 ~ n;
	int q, a, b;
	for (int i = 0; i < m; ++i) {
		cin >> q >> a >> b;
		if (q == 0) { // unite
			uf.unite(a, b);
		}
		else if (q == 1) { // is same?
			bool result = uf.is_same(a, b);
			if (result) cout << "YES\n";
			else cout << "NO\n";
		}
	}
	return 0;
}