// Ford-Fulkerson
#include <iostream>
#include <vector>
#include <algorithm>
#include <bitset>

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
bitset<SINK + 1> visited;

// src(0) -> worker(1~1000) -> work(1001~2000) -> sink(3000)

int fodfs(int v, int t, int f) {
	if (v == t) return f;

	visited[v] = 1;

	for (Edge& e : graph[v]) {
		if (visited[e.to]) continue;

		if (e.cap == 0) continue; // 빼먹지 않기!

		int flow = fodfs(e.to, t, min(f, e.cap));

		if (flow == 0) continue;

		e.cap -= flow;
		graph[e.to][e.rev].cap += flow;

		return flow;
	}

	return 0;
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	int N, M; cin >> N >> M; // 직원 1 ~ N, 일 1 ~ M
	const int WORKERNUM = N + 1;

	graph = vector<vector<Edge>>(SINK + 1);
	for (int n{ 1 }; n <= N; ++n) {
		int S{}; cin >> S;

		// src -> worker
		int srcRev = static_cast<int>(graph[0].size());
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
		visited.reset(); // 0 reset
		int flow = fodfs(s, d, INF);

		if (flow == 0) break;

		maxFlow += flow;
	}

	cout << maxFlow << '\n';

	return 0;
}