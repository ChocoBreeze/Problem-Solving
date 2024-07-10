#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Disjoint {
	vector<int> par, siz;

	Disjoint(int n) : par(n, -1), siz(n, 1) {}

	int root(int x) {
		if (par[x] == -1) return x;
		else return par[x] = root(par[x]);
	}

	bool unite(int x, int y) {
		x = root(x), y = root(y);
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
	Edge(int s, int d, int w) : src(s), dst(d), weight(w) {}
};

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	int N, M;
	cin >> N >> M;
	Disjoint D(N + 1); // 1 ~ N
	vector<Edge> Edges(M, Edge(0, 0, 0));
	for (auto& e : Edges) {
		cin >> e.dst >> e.src >> e.weight;
	}
	auto compare = [](Edge& a, Edge& b) {
		return a.weight < b.weight; // ascend
	};
	sort(begin(Edges), end(Edges),compare);
	int edge_count = 0;
	int answer = 0;
	for (auto& e : Edges) {
		if (edge_count == N - 1) break; // tree
		if (D.root(e.dst) == D.root(e.src)) continue;
		answer += e.weight;
		++edge_count;
		D.unite(e.src, e.dst);
	}
	cout << answer;
	return 0;
}