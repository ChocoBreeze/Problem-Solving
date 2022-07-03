// Kruskal
#include <iostream>
#include <queue> // priority_queue
#include <vector> // vector
#include <algorithm> // swap, sort, min

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
	int original_index;
	int x;
	int y;
	int z;
	Coord(int index, int x, int y, int z) : original_index(index), x(x), y(y), z(z) {}
};

struct Edge {
	int src;
	int dst;
	int weight;
	Edge(int src, int dst, int weight) : src(src), dst(dst), weight(weight) {}
};

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	int N;
	cin >> N;
	vector<Coord> pos(N, Coord(0, 0, 0, 0));
	for (int i = 0; i < N; ++i) {
		pos[i].original_index = i;
		cin >> pos[i].x >> pos[i].y >> pos[i].z;
	}
	Disjoint_Set d(N); // 1 ~ N
	auto compare = [](Edge& a, Edge& b) {
		return a.weight > b.weight;
	};
	priority_queue<Edge, vector<Edge>, decltype(compare)> PQ(compare);
	for (int i = 0; i < 3; ++i) { // 메모리 절약을 위한 sort 반복문. 참고 : https://www.acmicpc.net/source/45360822
		if (i == 0) sort(begin(pos), end(pos), [](Coord& a, Coord& b) {return a.x > b.x; });
		else if(i==1) sort(begin(pos), end(pos), [](Coord& a, Coord& b) {return a.y > b.y; });
		else sort(begin(pos), end(pos), [](Coord& a, Coord& b) {return a.z > b.z; });
		for (int k = 0; k < N; ++k) {
			for (int j = k + 1; j <= k + 2; ++j) {
				if (j >= N) break;
				int dist;
				if(i==0) dist = abs(pos[k].x - pos[j].x);
				else if(i==1) dist = abs(pos[k].y - pos[j].y);
				else dist = abs(pos[k].z - pos[j].z);
				PQ.push(Edge(pos[k].original_index, pos[j].original_index, dist));
			}
		}
	}
	int weight_sum = 0;
	while (!PQ.empty()) {
		Edge now = PQ.top();
		PQ.pop();
		if (d.is_same(now.dst, now.src)) continue;
		weight_sum += now.weight;
		d.unite(now.dst, now.src);
	}
	cout << weight_sum;
	return 0;
}