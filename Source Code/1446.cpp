#include <iostream>
#include <vector>
#include <algorithm> // min

using namespace std;

constinit const int INF = 1 << 30;

struct Edge {
	int to, weight;
	Edge(int to, int weight) : to(to), weight(weight) {}
	bool operator<(const Edge& e) const {
		return this->weight > e.weight;
	}
};

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int N{}, D{}; // 지름길 개수, 고속도로 길이
	cin >> N >> D;

	vector<vector<Edge>> graph(D + 1); // 0 ~ D

	for (int n{}; n < N; ++n) {
		int s{}, e{}, l{}; // 시작, 도착, 지름길
		cin >> s >> e >> l; 
		graph[s].emplace_back(e, l); // 지름길은 일방 통행!
	}

	vector<int> dist(D + 1, INF);
	dist[0] = 0;
	for (Edge& e : graph[0]) {
		if (e.to > D) continue;
		dist[e.to] = min(dist[e.to], dist[0] + e.weight);
	}
	for (int d = 1; d <= D; ++d) {
		dist[d] = min(dist[d], dist[d - 1] + 1);
		for (Edge& e : graph[d]) {
			if (e.to > D) continue;
			dist[e.to] = min(dist[e.to], dist[d] + e.weight);
		}
	}
	cout << dist[D] << '\n';

	return 0;
}