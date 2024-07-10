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
	bool issame(int x, int y) {
		x = root(x), y = root(y);
		return x == y;
	}

	bool unite(int x, int y) {
		x = root(x), y = root(y);
		if (x == y) return false;
		if (siz[x] < siz[y]) swap(x, y);
		par[y] = x;
		siz[x] += siz[y];
		return true;
	}
};

int main() {
	cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	int N, M; // N : 도시 수, M : 여행 계획에 속한 도시 수
	cin >> N >> M;
	UnionFind uf(N + 1); // 1 ~ N
	for (int i = 0; i < N; ++i) {
		int temp;
		for (int j = 0; j < N;++j) {
			cin >> temp;
			if (temp==1) {
				uf.unite(i + 1, j + 1);
			}
		}
	}
	vector<int> path(M,0);
	for (auto& i : path) {
		cin >> i;
	}
	bool chk = true;
	for (int i = 0; i < M - 1; ++i) {
		chk = uf.issame(path[i], path[i + 1]);
		if (!chk) break;
	}
	if (chk) cout << "YES";
	else cout << "NO";
	return 0;
}