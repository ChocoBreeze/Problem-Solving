#include <iostream>
#include <vector>
#include <queue>

using namespace std;

constinit const int INF = 1 << 30;

struct Edge {
	int to, weight;
	Edge(int to, int weight) : to(to), weight(weight) {}
	bool operator<(const Edge& other) const {
		return weight > other.weight; // min heap
	}
};

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int N, M; cin >> N >> M;
	vector<vector<Edge>> graph(N + 1);
	for (int m{}; m < M; ++m) {
		int a, b, c;
		cin >> a >> b >> c;
		graph[a].emplace_back(b, c);
		graph[b].emplace_back(a, c);
	}

	vector<int> dist(N + 1, INF);
	dist[1] = 0;
	priority_queue<Edge> pq;
	pq.emplace(1,0);
	while (!pq.empty()) {
		Edge now = pq.top(); pq.pop();
		if (now.weight != dist[now.to]) continue;
		for (auto& [next, weight] : graph[now.to]) {
			if (dist[next] > now.weight + weight) {
				dist[next] = now.weight + weight;
				pq.emplace(next, dist[next]);
			}
		}
	}
	cout << dist[N] << '\n';

	return 0;
}