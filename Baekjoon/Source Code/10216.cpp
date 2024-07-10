#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric> // accumulate

using namespace std;
struct Circle {
	int x, y, r;
	Circle(int x, int y, int r) : x(x), y(y), r(r) {}
};

struct UnionFind {
	vector<int> par, visited;
	UnionFind(int n) : par(n, -1), visited(n,0) {}
	int Find(int a) {
		if (par[a] < 0) return a;
		return par[a] = Find(par[a]);
	}
	void Union(int a, int b) {
		a = Find(a), b = Find(b);
		if (a == b) return;
		if (-par[a] < -par[b]) swap(a, b);
		par[a] += par[b]; // a 밑에 b 달기
		par[b] = a;
	}
	int CountGroup() {
		for (int p{}; p < static_cast<int>(par.size());++p) {
			visited[Find(p)] = 1;
		}
		return accumulate(begin(visited), end(visited), 0); // 합 리턴
	}
};

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int T{}; cin >> T;
	while (T--) {
		int N{}; cin >> N;
		vector<Circle> circles(N, Circle(0, 0, 0));
		UnionFind uf(N);
		for (Circle& c : circles) cin >> c.x >> c.y >> c.r;
		for (int i{}; i < N; ++i) {
			auto& c1 = circles[i];
			for (int j{ i + 1 }; j < N; ++j) {
				auto& c2 = circles[j];
				if ((c1.x - c2.x) * (c1.x - c2.x) + (c1.y - c2.y) * (c1.y - c2.y) <= (c1.r + c2.r) * (c1.r + c2.r)) {
					uf.Union(i, j);
				}
			}
		}
		cout << uf.CountGroup() << '\n';
	}
	return 0;
}
