// KRUSKAL
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct Edge {
	int src;
	int dst;
	int weight;
	Edge(int s, int d, int w) : src(s), dst(d), weight(w) {}
	bool operator<(const Edge& other) const {
		return this->weight > other.weight;
	}
};

struct Union_Find {
	vector<int> par, siz;

	Union_Find(int n) : par(n, -1), siz(n, 1) {}

	int root(int x) {
		if (par[x] == -1) return x;
		else return par[x] = root(par[x]);
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
	ios::sync_with_stdio(false);
	int N, M;
	cin >> N >> M;
	int a, b, c;
	Union_Find U(N + 1); // 1 ~ N
	priority_queue<Edge> PQ;
	for (int m = 0; m < M; ++m) {
		cin >> a >> b >> c;
		PQ.push(Edge(a, b, c));
	}
	int count = 0, answer = 0;
	while (count < N - 2 && !PQ.empty()) { // N - 2개 뽑기
		Edge now = PQ.top();
		PQ.pop();
		if (U.root(now.src) == U.root(now.dst)) continue;
		count++;
		answer += now.weight;
		U.unite(now.src, now.dst);
	}
	cout << answer;
	
	return 0;
}
