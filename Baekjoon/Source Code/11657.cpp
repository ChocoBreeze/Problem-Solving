// bellman-ford
// 가중치가 음수인 경우는 dijkstra 못 씀!
#include<iostream>
#include<vector>
#include<climits> // INT_MAX

using std::cin;
using std::cout;
using std::vector;

struct Edge {
	int to;
	int weight;
	Edge(int t, int w) : to(t), weight(w) {}
};

using Graph = vector<vector<Edge>>;

int main() {
	cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	int N, M;
	int A, B, C;
	cin >> N >> M;
	Graph graph(N + 1);
	for (int i = 0; i < M; ++i) {
		cin >> A >> B >> C;
		graph[A].push_back(Edge(B, C));
	}
	bool is_neg_cycle = false;
	vector<long long> dist(N + 1, INT_MAX);
	dist[1] = 0; // start
	for (int i = 0; i < N; ++i) {
		bool is_update = false;
		for (int j = 1; j <= N; ++j) {
			if (dist[j] == INT_MAX) continue;
			for (auto k : graph[j]) {
				if (dist[k.to] > dist[j] + k.weight) {
					dist[k.to] = dist[j] + k.weight;
					is_update = true;
				}
			}
		}
		if (!is_update) break;
		if (i == N - 1 && is_update) is_neg_cycle = true;
	}
	if (is_neg_cycle) cout << -1;
	else {
		for (int i = 2; i <= N; ++i) {
			if (dist[i] < INT_MAX) cout << dist[i] << "\n";
			else cout << "-1\n";
		}
	}
	return 0;
}