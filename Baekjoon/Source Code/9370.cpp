// Dijkstra
/*
도착지까지 최단거리로 가기때문에
g h 사이의 도로를 지난 최단거리와 s에서 최단거리가 일치하는 경우에 정답이 된다.
*/
#include<iostream>
#include<vector>
#include<queue> // priority_queue
#include<climits> // INT_MAX
#include<algorithm> // sort

using std::cout;
using std::cin;
using std::vector;
using std::priority_queue;
using std::greater;
using std::pair;
using std::make_pair;
using std::sort;

struct Edge {
	int to;
	int weight;
	Edge(int t, int w) : to(t), weight(w) {}
};

using Graph = vector<vector<Edge>>; // 간선 저장
using Data = pair<long long, int>; // 거리, 꼭짓점

void dijkstra(Graph& graph, vector<long long>& dist,int start) {
	priority_queue<Data, vector<Data>, greater<Data>> PQ;
	PQ.push(make_pair(dist[start], start));
	while (!PQ.empty()) {
		Data now = PQ.top();
		PQ.pop();
		if (now.first > dist[now.second]) continue; // 완화할 필요 없음
		for (auto& i : graph[now.second]) {
			if (dist[i.to] > dist[now.second] + i.weight) {
				dist[i.to] = dist[now.second] + i.weight;
				PQ.push(make_pair(dist[i.to], i.to));
			}
		}
	}
}

int main() {
	cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	int T;
	cin >> T;
	for (int k = 0; k < T; ++k) {
		int n, m, t;
		cin >> n >> m >> t; // 정점 수, 간선 수, 목적지 후보 수
		int s, g, h, g_h_cost;
		cin >> s >> g >> h; // 출발지, 지나야 하는 도로(g - h)
		Graph graph(n + 1); // 1~n
		int a, b, d; // a -> b : d의 비용
		for (int i = 0; i < m; ++i) { // weight 저장
			cin >> a >> b >> d;
			if ((a == g && b == h) || (a == h && b == g)) g_h_cost = d;
			graph[a].push_back(Edge(b, d));
			graph[b].push_back(Edge(a, d));
		}
		vector<int> goal_candidate(t, 0);
		for (int i = 0; i < t; ++i) {
			cin >> goal_candidate[i];
		}

		// s에서 dijkstra
		vector<long long> dist_s(n + 1, INT_MAX);
		dist_s[s] = 0;
		dijkstra(graph, dist_s, s);
		// 정해진 도로를 지나는 dijkstra
		vector<long long> dist_g(n + 1, INT_MAX);
		dist_g[g] = 0;
		dijkstra(graph, dist_g, g);

		vector<long long> dist_h(n + 1, INT_MAX);
		dist_h[h] = 0;
		dijkstra(graph, dist_h, h);

		vector<int> answer;
		for (auto& i : goal_candidate) {
			if (dist_s[i] == dist_s[g] + g_h_cost + dist_h[i] || dist_s[i] == dist_s[h] + g_h_cost + dist_g[i])
				answer.push_back(i);
		}
		sort(answer.begin(), answer.end());
		for (auto& i : answer) {
			cout << i << " ";
		}
		cout << "\n";
	}
	return 0;
}