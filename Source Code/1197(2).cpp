// kruskal
// weight들을 min_heap에 추가. -> 싸이클이 아닌 경우 Tree 만들기
#include <iostream>
#include <vector>
#include <queue> // min_heap
#include <algorithm>

using namespace std;

struct DisJoint {
	vector<int> par, siz;

	DisJoint(int n) : par(n, -1), siz(n, 1) {}

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
		if (siz[x] < siz[y]) {
			swap(x, y);
		}
		par[y] = x;
		siz[x] += siz[y];
		return true;
	}
};

struct Edge {
	int src;
	int dst;
	int weight;
	Edge(int src, int dst, int weight) : src(src), dst(dst), weight(weight) {}

	inline bool operator< (const Edge& e) const {
		return this->weight < e.weight;
	}
	inline bool operator> (const Edge& e) const {
		return this->weight > e.weight;
	}
};

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	int V, E;
	cin >> V >> E;
	DisJoint D(V + 1); // 1 ~ V
	priority_queue<Edge, vector<Edge>, greater<Edge>> PQ;
	for (int e = 1; e <= E; ++e) {
		int A, B, C;
		cin >> A >> B >> C; // A -> B (C)
		PQ.push(Edge(A, B, C));
	}
	int weight_sum = 0;
	while (!PQ.empty()) {
		auto e = PQ.top();
		PQ.pop();
		int x = e.src, y = e.dst;
		if (D.is_same(x, y)) continue;
		D.unite(x, y);
		weight_sum += e.weight;
	}
	cout << weight_sum;
	return 0;
}