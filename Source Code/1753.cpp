// 방향 그래프
// Dijkstra
// 이미 최단 경로가 확정된 정점 집합 S를 관리.
// 매 번 S에 포함되지 않은 정점들에 대해 거리가 최소인 정점을 S에 추가 후
// 해당하는 최소 거리로 시작점 s에서 다른 정점들로의 거리들을 완화
// O(|V|^2) --> 시간 초과s
// Heap으로 변경
#include<iostream>
#include<vector> 
#include<climits>
#include<queue> // priority_queue

using std::cout;
using std::cin;
using std::vector;
using std::priority_queue;
using std::pair;
using std::make_pair;

const int INF = INT_MAX;

struct Edge {
	int to;
	int weight;
	Edge(int to, int weight) : to(to), weight(weight) {}
};

int main() {
	cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	int V, E, s;
	cin >> V >> E; // 정점 수, 간선 수
	cin >> s; // 시작 정점
	vector<vector<Edge>> edges(V + 1); // 1~V
	for (int i = 0; i < E; ++i) {
		int u, v, w;
		cin >> u >> v >> w;
		edges[u].push_back(Edge(v, w));
	}
	vector<bool> S(V + 1); // 1~V
	vector<int> distance_s(V + 1,INF);
	distance_s[s] = 0;
	priority_queue<pair<int, int>, vector<pair<int,int>>, std::greater<pair<int,int>>> Q; // max_heap
	Q.push(make_pair(distance_s[s], s));
	while(!Q.empty()) { // for문이 도는 횟수 = 정점 개수
		// 1. 거리가 최소인 정점 찾기(S에 포함되지 않은 정점 중에) --> Heap으로 개선
		
		int min_dist = Q.top().first;
		int min_v = Q.top().second;
		Q.pop();

		if (min_dist > distance_s[min_v]) continue; // 완화할 필요 없음

		// 2. 각 정점들의 거리 완화
		for (auto& e : edges[min_v]) { 
			if (distance_s[e.to] > distance_s[min_v] + e.weight) {
				distance_s[e.to] = distance_s[min_v] + e.weight;
				Q.push(make_pair(distance_s[e.to], e.to));
			}
		}
		S[min_v] = true;
	}

	for (int i = 1; i <= V; ++i) {
		if (distance_s[i] < INF) cout << distance_s[i] << "\n";
		else cout << "INF\n";
	}
	return 0;
}