// N번 돌리지 않고도 neg cycle를 찾을 수 있는지가 관건!
// 최단 거리가 목표가 아닌 neg cycle 존재 유무 판별이 목표임
// https://www.acmicpc.net/board/view/72995 - 정리가 잘 되어 있음
#include <iostream>
#include <vector>

using namespace std;

struct e_t {
	int dst;
	int weight;
	e_t(int d, int w) : dst(d), weight(w) {}
};

const int INF = 1000000000;

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	int T, N, M, W;
	cin >> T;
	for (int t = 0; t < T; ++t) {
		cin >> N >> M >> W;
		vector<vector<e_t>> edges(N + 1); // 1 ~ N
		int s, e, w;
		for (int m = 0; m < M; ++m) {
			cin >> s >> e >> w;
			// 방향성 x
			edges[s].push_back(e_t(e, w));
			edges[e].push_back(e_t(s, w));
		}
		for (int i = 0; i < W; ++i) {
			cin >> s >> e >> w;
			edges[s].push_back(e_t(e, -w));
		}
		bool neg_cycle = false;

		vector<int> dist(N + 1, INF);
		for (int n = 0; n < N; ++n) { // 정점 N번
			for (int i = 1; i <= N; ++i) {
				// if (dist[i] == INF) continue;
				for (auto& edge : edges[i]) {
					if (dist[edge.dst] > dist[i] + edge.weight) {
						if (n == N - 1) { // N번째인 경우 neg cycle
							neg_cycle = true;
							break;
						}
						dist[edge.dst] = dist[i] + edge.weight;
					}
				}
			}
		}
		if (neg_cycle) cout << "YES\n";
		else cout << "NO\n";
	}
	return 0;
}