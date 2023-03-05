// 방향 그래프
// Dijkstra
// 이미 최단 경로가 확정된 정점 집합 S를 관리.
// 매 번 S에 포함되지 않은 정점들에 대해 거리가 최소인 정점을 S에 추가 후
// 해당하는 최소 거리로 시작점 s에서 다른 정점들로의 거리들을 완화
// O(|V|^2) --> 시간 초과s
// Heap으로 변경
#include <iostream>
#include <vector>
#include <queue>
#include <utility>

using namespace std;

const int INF = 2e9;

using pii = pair<int, int>;

struct Edge {
	int to;
	int weight;
	Edge(int to, int weight) : to(to), weight(weight) {}
};

int main() {
	cin.tie(NULL)->sync_with_stdio(false);
	int V, E, s;
	cin >> V >> E >> s; // 정점 개수, 간선 개수, 시작점
	
	vector<vector<Edge>> edges(V + 1); // 1 ~ V
	for (int i = 0; i < E; ++i) {
		int u, v, w;
		cin >> u >> v >> w;
		edges[u].push_back(Edge(v, w));
	}

	vector<int> distance(V + 1, INF);
	distance[s] = 0;
	priority_queue<pii, vector<pii>, greater<pii>> Q;
	Q.push(make_pair(distance[s], s));

	while (!Q.empty()) {
		int dist = Q.top().first;
		int v = Q.top().second;
		Q.pop();

		if (dist > distance[v]) continue;

		for (auto& e : edges[v]) {
			if (distance[e.to] > distance[v] + e.weight) {
				distance[e.to] = distance[v] + e.weight;
				Q.push(make_pair(distance[e.to], e.to));
			}
		}

	}

	for (int i = 1; i <= V; ++i) {
		if (distance[i] < INF) cout << distance[i] << '\n';
		else cout << "INF\n";
	}


	return 0;
}