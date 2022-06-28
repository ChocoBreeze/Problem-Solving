#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

using std::cin;
using std::cout;
using std::vector;
using std::swap;
using Graph = vector<vector<int>>;

struct UnionFind {
	vector<int> par, siz;
	vector<bool> chk;

	UnionFind(int n) : par(n, -1), siz(n, 1), chk(n, true) {}

	int root(int x) {
		if (par[x] == -1) return x; // x가 루트이면 x 반환
		else return par[x] = root(par[x]);
	}

	bool unite(int x, int y) {
		x = root(x), y = root(y);
		if (x == y || !chk[x] || !chk[y]) return false;
		if (siz[x] < siz[y]) swap(x, y);
		par[y] = x;
		siz[x] += siz[y];
		return true;
	}
};

int main() {
	cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	int n, m;
	for (int j = 1; ; ++j) {
		cin >> n >> m;
		if (n == 0 && m == 0) break;
		UnionFind uf(n + 1); // 1 ~ n
		int a, b;
		for (int i = 0; i < m; ++i) {
			cin >> a >> b;
			bool result = uf.unite(a, b);
			if (!result) {
				uf.chk[a] = false;
				uf.chk[b] = false;
				int root1 = uf.root(a), root2 = uf.root(b);
				for (int k = 1; k < size(uf.par); ++k) {
					if (k==root1 || k==root2 || uf.par[k] == root1 || uf.par[k] == root2) uf.chk[k] = false;
				}
			}
		}
		int tree_cnt = 0;
		for (int k = 1; k < size(uf.par); ++k) {
			if (uf.chk[k] && uf.par[k]==-1) ++tree_cnt;
		}
		cout << "Case " << j << ": ";
		if (tree_cnt > 1)
			cout << "A forest of " << tree_cnt << " trees.\n";
		else if (tree_cnt == 1)
			cout << "There is one tree.\n";
		else
			cout << "No trees.\n";
	}
	return 0;
}