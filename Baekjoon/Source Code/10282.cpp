#include <iostream>
#include <vector>
#include <algorithm> // max
#include <queue> // priority_queue

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
	int T{}; cin >> T;
	while (T--) {
		int n, d, c; // 컴퓨터 개수(정점 수), 의존성 개수(간선 수), 해킹당한 컴퓨터 번호(시작점)
		cin >> n >> d >> c;

		vector<vector<Edge>> graph(n + 1); // 1 ~ n
		for (int i{}; i < d; ++i) {
			int a, b, s; // b -> a (s)
			cin >> a >> b >> s;
			graph[b].emplace_back(a, s);
		}

		vector<int> dist(n + 1, INF);
		dist[c] = 0; // 시작점
		priority_queue<Edge> pq; // min heap
		pq.emplace(c, 0);
		while (!pq.empty()) {
			Edge now = pq.top(); pq.pop();
			if (now.weight > dist[now.to]) continue;
			for (auto& e : graph[now.to]) {
				if (dist[e.to] > now.weight + e.weight) {
					dist[e.to] = now.weight + e.weight;
					pq.emplace(e.to, dist[e.to]);
				}
			}
		}

		// 감염되는 컴퓨터 수 = 도달 가능한 경우
		// 마지막 컴퓨터가 감염되기까지 걸리는 시간 = 최대값
		int maxDist{}, cnt{};
		for (int& di : dist) {
			if (di != INF) {
				++cnt;
				maxDist = max(maxDist, di);
			}
		}
		cout << cnt << ' ' << maxDist << '\n';
	}

	return 0;
}