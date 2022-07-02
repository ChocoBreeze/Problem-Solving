// Prim - 하나의 트리를 확장하는 것이 아니라 안 될 거 같음
// Kruskal로 품
// 숫자 범위를 잘 보세요..
#include <iostream>
#include <queue> // priority_queue
#include <vector> // vector
#include <algorithm> // swap
#include <cmath> // sqrt

using namespace std;

struct Disjoint_Set {
	vector<int> siz, par;
	Disjoint_Set(int n) : siz(n, 1), par(n, -1) {}

	int root(int x) {
		if (par[x] == -1) return x;
		else return root(par[x]);
	}
	
	bool is_same(int x, int y) {
		x = root(x);
		y = root(y);
		return x == y;
	}

	bool unite(int x, int y) {
		x = root(x);
		y = root(y);
		if (x == y) return false;
		if (siz[x] < siz[y]) swap(x, y);
		par[y] = x;
		siz[x] += siz[y];
		return true;
	}
};

struct Coord {
	int x;
	int y;
	Coord(int x, int y) : x(x), y(y) {}
};

struct Edge {
	int src;
	int dst;
	double weight;
	Edge(int src, int dst, double weight) : src(src), dst(dst), weight(weight) {}
};

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	int N, M;
	cin >> N >> M;
	vector<Coord> pos(N + 1, Coord(0, 0));
	for (int i = 1; i <= N; ++i) {
		cin >> pos[i].x >> pos[i].y;
	}
	Disjoint_Set d(N + 1); // 1 ~ N
	for (int i = 0; i < M; ++i) {
		int a, b;
		cin >> a >> b;
		d.unite(a, b);
	}
	auto compare = [](Edge& a, Edge& b) {
		return a.weight > b.weight;
	};
	priority_queue<Edge, vector<Edge>, decltype(compare)> PQ(compare);
	for (int i = 1; i <= N; ++i) {
		for (int j = i + 1; j <= N; ++j) {
			long long dist_x = pos[i].x - pos[j].x, dist_y = pos[i].y - pos[j].y;
			double distance = sqrt(dist_x * dist_x + dist_y * dist_y);
			PQ.push(Edge(i, j, distance));
		}
	}
	double weight_sum = 0;
	while (!PQ.empty()) {
		Edge now = PQ.top();
		PQ.pop();
		if (d.is_same(now.dst, now.src)) continue;
		weight_sum += now.weight;
		d.unite(now.dst, now.src);
	}
	cout << fixed;
	cout.precision(2);
	cout << weight_sum;
	return 0;
}