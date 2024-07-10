// 다익스트라 두 번
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct e_t {
	int to;
	int weight;
	e_t(int t, int w) : to(t), weight(w) {}
};

const int INF = 1000000000;

void dijkstra(vector<vector<e_t>>& edges, vector<int>& dist, int start) {
	auto compare = [](const e_t& a, const e_t& b) {
		return a.weight > b.weight;
	};
	priority_queue <e_t, vector<e_t>, decltype(compare)> PQ(compare);

	PQ.push(e_t(start, 0));
	dist[start] = 0;
	while (!PQ.empty()) {
		e_t now = PQ.top();
		PQ.pop();
		if (now.weight > dist[now.to]) continue;
		for (auto& next : edges[now.to]) {
			if (dist[next.to] > now.weight + next.weight) {
				dist[next.to] = now.weight + next.weight;
				PQ.push(e_t(next.to, dist[next.to]));
			}
		}
	}
}

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	int N, M, X;
	int a, b, c;
	cin >> N >> M >> X;
	vector<vector<e_t>> edges(N + 1); // 올 때
	vector<vector<e_t>> edges_reverse(N + 1); // 갈 때
	for (int m = 0; m < M; ++m) {
		cin >> a >> b >> c;
		edges[a].push_back(e_t(b, c)); // 단방향 간선
		edges_reverse[b].push_back(e_t(a, c)); // 단방향 간선
	}
	
	vector<int> dist_go(N + 1, INF);
	vector<int> dist_come(N + 1, INF);
	dijkstra(edges_reverse, dist_go, X);
	dijkstra(edges, dist_come, X);
	
	int answer = -1;
	for (int i = 1; i <= N; ++i) {
		answer = max(answer, dist_go[i] + dist_come[i]);
	}
	cout << answer;
	return 0;
}