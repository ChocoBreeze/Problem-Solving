// https://www.acmicpc.net/board/view/93932
// https://www.acmicpc.net/board/view/29519
// 코드 구현에서 이상한 값 넣은 게 한 두 가지가 아니다.(bfs)
#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

struct e_t {
	int to;
	long long weight;
	e_t(int t, long long w) : to(t), weight(w) {}
};

const long long INF = LLONG_MAX;

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	int N, S, E, M, a, b, c;
	cin >> N >> S >> E >> M;
	vector<vector<e_t>> edges(N); // 0 ~ N - 1
	for (int m = 0; m < M; ++m) {
		cin >> a >> b >> c;
		edges[a].push_back(e_t(b, c));
	}
	// 벌 수 있는 돈
	vector<int> earn(N, 0);
	for (auto& i : earn) {
		cin >> i;
	}
	// edge 갱신
	for (int n = 0; n < N; ++n) {
		for (auto& e : edges[n]) {
			e.weight -= earn[e.to];
		}
	}
	// bellman-ford
	vector<long long> dist(N, INF);
	// neg_cycle check
	vector<bool> vertex(N, false);
	bool is_neg_cycle = false;
	dist[S] = -earn[S]; // 0이 아닌 것에 주의
	for (int i = 0; i < N; ++i) { // 갱신횟수
		for (int n = 0; n < N; ++n) {
			if (dist[n] == INF) continue;
			for (auto& e : edges[n]) {
				if (dist[e.to] > dist[n] + e.weight) {
					dist[e.to] = dist[n] + e.weight;
					if (i == N - 1) { // neg cycle
						vertex[n] = true;
						is_neg_cycle = true;
					}
				}
			}
		}
	}
	
	
	if (dist[E] == INF) {
		cout << "gg";
	}
	// neg cycle이 도착점과 관련 있는지가 중요함.
	else if (is_neg_cycle) { // cycle에 end가 포함되어있는지 한 번더 확인
		bool cycle_contain_end = false;
		for (int n = 0; n < N; ++n) {
			if (vertex[n]) { // cycle이 여러 개 있을 수도 있지 않을까? 하고 생각
				vector<bool> visited(N, false);
				queue<int> Q;
				Q.push(n);
				visited[n] = true;
				while (!Q.empty()) {
					int now = Q.front();
					Q.pop();
					for (auto& e : edges[now]) {
						if (e.to == E) {
							cycle_contain_end = true;
							break;
						}
						if (!visited[e.to]) {
							Q.push(e.to); // 다음 정점
							visited[e.to] = true;
						}
					}
					if (cycle_contain_end) break;
				}
			}
			if (cycle_contain_end) break;
		}
		if (cycle_contain_end) cout << "Gee";
		else cout << dist[E] * (-1);
	}
	else {
		cout << dist[E] * (-1);
	}
	return 0;
}