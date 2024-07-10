// Edmonds-Karp
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

constinit const int SRC = 0;
constinit const int SINK = 3000;
constinit const int WORK = 1000;
constinit const int INF = 1 << 30;

struct Edge {
	int rev, from, to, cap;
	Edge(int r, int f, int t, int c) : rev(r), from(f), to(t), cap(c) {}
};

vector<vector<Edge>> graph;

// src(0) -> worker(1~1000) -> work(1001~2000) -> sink()

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	int N, M; cin >> N >> M; // 직원 1 ~ N, 일 1 ~ M
	const int WORKERNUM = N + 1;

	graph = vector<vector<Edge>>(SINK + 1);
	for (int n{ 1 }; n <= N; ++n) {
		int S{}; cin >> S;

		// src -> worker
		int srcRev = static_cast<int>(graph[SRC].size());
		int fromRev = static_cast<int>(graph[n].size());
		graph[0].emplace_back(fromRev, 0, n, 2); // cap = 2 - 각 직원은 최대 두 개의 일을 할 수 있고
		graph[n].emplace_back(srcRev, n, 0, 0); // cap = 0 (가상)

		for (int s{}; s < S; ++s) {
			int work; cin >> work;
			work += WORKERNUM;
			// worker -> work
			int toRev = static_cast<int>(graph[work].size());
			fromRev = static_cast<int>(graph[n].size());
			graph[n].emplace_back(toRev, n, work, INF); // capacity 아무거나줘도 상관 없음.
			graph[work].emplace_back(fromRev, work, n, 0); // cap = 0 (가상)
		}
	}

	for (int m{ 1 }; m <= M; ++m) {
		int work = m + WORKERNUM;
		int toRev = static_cast<int>(graph[work].size());
		int sinkRev = static_cast<int>(graph[SINK].size());

		// work -> sink
		graph[work].emplace_back(sinkRev, work, SINK, 1); // cap = 1 - 각각의 일을 담당하는 사람은 1명
		graph[SINK].emplace_back(toRev, SINK, work, 0); // cap = 0 (가상)
	}

	int maxFlow{}, s{ SRC }, d{ SINK };
	while (1) {
		vector<int> prevVisited(SINK + 1, -1);
		vector<pair<int, int>> path(SINK + 1);
		// path[i] : Edge e의 to가 i인 간선의 {from, index} 저장
		// index : from -> i의 간선이 from의 몇 번째 index인지.

		queue<int> Q;
		Q.push(s);

		while (!Q.empty() && prevVisited[d] == -1) {
			int now = Q.front(); Q.pop();
			int index{};
			for (Edge& e : graph[now]) {
				if (e.cap > 0 && prevVisited[e.to] == -1) {
					prevVisited[e.to] = now;
					Q.push(e.to);
					path[e.to] = make_pair(now, index);
					if (e.to == d) break; // 이거 차이가 시간 차이인가?
				}
				++index;
			}
		}

		if (prevVisited[d] == -1) break;

		int flow{ INF };
		for (int i{ d }; i != s; i = prevVisited[i]) {
			flow = min(flow, graph[path[i].first][path[i].second].cap);
		}
		for (int i{ d }; i != s; i = prevVisited[i]) {
			Edge& e = graph[path[i].first][path[i].second];
			e.cap -= flow;
			graph[e.to][e.rev].cap += flow;
		}
		maxFlow += flow;
	}
	cout << maxFlow << '\n';

	return 0;
}