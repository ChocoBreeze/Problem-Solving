// 1 ~ N 까지 최단 거리 but 반드시 거쳐야 하는 정점이 존재.
// Dijkstra
// 기존에는 v2에서 시작해서 최단 경로를 측정하지 않고 N에서 쟀는데,
// 의도한 결과가 나오지 않은 것 같음.
#include<iostream>
#include<vector>
#include<algorithm> // min
#include<queue> // min heap
#include<utility> //pair

struct Edge {
	int to;
	int weight;
	Edge(int to, int weight) : to(to), weight(weight) {}
};

using std::cin;
using std::cout;
using std::vector;
using std::min;
using std::priority_queue;
using std::pair;
using std::make_pair;
using Graph = vector<vector<Edge>>;

const int INF = 200000001; // 200000 * 1000 = 200000000

void dijkstra(Graph& graph, vector<int>& dist, int s) {
	priority_queue<pair<int, int>, vector<pair<int, int>>, std::greater<pair<int, int>>> Q;
	Q.push(make_pair(dist[s],s));

	while (!Q.empty()) {
		int v = Q.top().second; // 거리 최소인 꼭짓점
		int d = Q.top().first; // 미사용 꼭짓점 중 거리 최소
		Q.pop();
		if (d > dist[v]) continue; // 완화 필요 없음
		for (auto& e : graph[v]) { // 완화 시작
			if (dist[e.to] > dist[v] + e.weight) {
				dist[e.to] = dist[v] + e.weight;
				Q.push(make_pair(dist[e.to], e.to)); // 기존 값 제거 안해도 영향 없음
			}
		}
	}
}

int main() {
	cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	int N, E; // 정점 수, 간선 수
	int a, b, c, v1, v2;
	cin >> N >> E;
	// undirected weighted graph
	Graph graph(N + 1); // 1 ~ N
	for (int i = 0; i < E; ++i) {
		cin >> a >> b >> c;
		graph[a].push_back(Edge(b, c));
		graph[b].push_back(Edge(a, c));
	}
	cin >> v1 >> v2;
	// 1에서 시작하는 최단 거리
	// 1->v1, 1->v2 
	vector<int> dist_1(N + 1, INF); 
	dist_1[1] = 0;
	dijkstra(graph, dist_1, 1);

	// v1에서 시작하는 최단 거리
	// v1 -> v2, v1-> N
	vector<int> dist_v1(N + 1, INF);
	dist_v1[v1] = 0;
	dijkstra(graph, dist_v1, v1);

	// v2에서 시작하는 최단 거리
	// v2 -> N, v2 -> v1
	vector<int> dist_v2(N + 1, INF);
	dist_v2[v2] = 0;
	dijkstra(graph, dist_v2, v2);
	int path1, path2;
	if (dist_1[v1] >= INF || dist_v1[v2] >= INF || dist_v2[N] >= INF) path1 = INF; 
	else path1 = dist_1[v1] + dist_v1[v2] + dist_v2[N]; // 1 -> v1 -> v2 -> N
	if (dist_1[v2] >= INF || dist_v2[v1] >= INF || dist_v1[N] >= INF) path2 = INF;
	else path2 = dist_1[v2] + dist_v2[v1] + dist_v1[N]; // 1 -> v2 -> v1 -> N
	if (path1 == INF && path2 == INF) cout << -1;
	else cout << min(path1, path2);

	return 0;
}