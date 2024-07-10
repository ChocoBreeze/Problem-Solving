// Ford-Fulkerson
// https://www.acmicpc.net/problem/2188 똑같이
#include <iostream>
#include <vector>
#include <algorithm>
#include <bitset>

using namespace std;

constinit const int SINK = 3000;
constinit const int WORK = 1000;
constinit const int INF = 1 << 30;

struct Edge {
	int rev, from, to, cap;
	Edge(int r, int f, int t, int c) : rev(r), from(f), to(t), cap(c) {}
};

vector<vector<Edge>> graph;
bitset<SINK + 1> visited;

// src(0) -> worker(1~1000) -> work(1001~2000) -> sink()

int fodfs(int v, int t, int f) {
	if (v == t) return f;

	visited[v] = 1;

	for(Edge& e : graph[v]) {
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
	for (int n{1}; n <= N; ++n) {
		int S{}; cin >> S;

		// src -> worker
		int srcRev = static_cast<int>(graph[0].size());
		int fromRev = static_cast<int>(graph[n].size());
		graph[0].emplace_back(fromRev, 0, n, 1);
		graph[n].emplace_back(srcRev, n, 0, 0); // 반대 간선은 없음

		for (int s{}; s < S; ++s) {
			int work; cin >> work;
			work += WORKERNUM;
			// worker -> work
			int toRev = static_cast<int>(graph[work].size());
			fromRev = static_cast<int>(graph[n].size());
			graph[n].emplace_back(toRev, n, work, 1); // capacity 아무거나줘도 상관 없음.
			graph[work].emplace_back(fromRev, work, n, 0);
		}
	}

	for (int m{ 1 }; m <= M; ++m) {
		int work = m + WORKERNUM;
		int toRev = static_cast<int>(graph[work].size());
		int sinkRev = static_cast<int>(graph[SINK].size());

		// work -> sink
		graph[work].emplace_back(sinkRev, work, SINK, 1); // cap = 1;
		graph[SINK].emplace_back(toRev, SINK, work, 0);
	}

	int maxFlow{}, s{}, d{ SINK };
	while (1) {
		visited.reset(); // 0 reset
		int flow = fodfs(s, d, INF);

		if (flow == 0) break;

		maxFlow += flow;
	}

	cout << maxFlow << '\n';

	return 0;
}