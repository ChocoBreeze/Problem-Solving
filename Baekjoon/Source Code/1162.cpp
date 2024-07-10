// 첫 아이디어 : 다익스트라 계산 후 table 계산
// k + 1 하는 과정에서 해당 간선이 없어졌다는 사실을 다른 경로에는 반영이 불가능!

// 이 아이디어 : 다익스트라 계산 하면서 다음 K도 갱신

#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <climits>

using namespace std;

const long long INF = LLONG_MAX;
struct Data {
	int v;
	int k;
	long long dist;
	Data(int v, int k, long long dist) : v(v), k(k), dist(dist) {}
};

struct Edge {
	int s;
	int cost;
	Edge(int s, int cost) : s(s), cost(cost) {}
};

int main() {
	cin.tie(NULL)->sync_with_stdio(false);
	int N, M, K, a, b, c;
	cin >> N >> M >> K;

	vector<vector<Edge>> graph(N + 1); // 1 ~ N
	for (int m = 0; m < M; ++m) {
		cin >> a >> b >> c;
		graph[a].push_back(Edge(b, c));
		graph[b].push_back(Edge(a, c));
	}

	auto compare = [](const Data& d1, const Data& d2) {
		return d1.dist > d2.dist;
	};
	priority_queue<Data, vector<Data>, decltype(compare)> Q(compare);
	vector<vector<long long>> dist(K+1, vector<long long>(N+1, INF));
	for (int k = 0; k <= K; ++k) {
		dist[k][1] = 0;
		Q.push(Data(1, k, 0)); // 거리, 정점
	}
	
	while (!Q.empty()) {
		int now_v = Q.top().v;
		int now_k = Q.top().k;
		long long now_dist = Q.top().dist;
		Q.pop();
		
		if (now_dist > dist[now_k][now_v]) continue; // 갱신할 필요 없음
		for (auto& e : graph[now_v]) {
			// 기존 dijkstra
			long long new_cost = now_dist + e.cost;
			if (dist[now_k][e.s] > new_cost) {
				dist[now_k][e.s] = new_cost;
				Q.push(Data(e.s, now_k, new_cost));
			}
			// 새 k 갱신
			if (now_k < K) {
				int new_k = now_k + 1;
				new_cost = now_dist;
				if (new_cost < dist[new_k][e.s]) {
					dist[new_k][e.s] = new_cost;
					Q.push(Data(e.s, new_k, new_cost));
				}
			}
		}
	}
	cout << dist[K][N] << '\n';
	
	return 0;
}