// 공부
// https://m.blog.naver.com/kks227/220804885235
// Ford-Fulkerson
#include <iostream>
#include <vector>
#include <algorithm>
#include <bitset>

using namespace std;

constinit const int SINK = 500;
constinit const int INF = 1 << 30;
constinit const int barnStart = 200;

struct Edge {
	int rev, from, to, cap;
	Edge(int r, int f, int t, int c) : rev(r), from(f), to(t), cap(c) {}
};

vector<vector<Edge>> graph;
bitset<SINK + 1> visited;

// 0(source) -> 소들(1 ~ N) -> 축사(barnStart + M(1 ~ M)) -> 목적지(500)(sink)

/**
* 최소 용량 발견 시 해당 용량 반환
* 최소 용량 발견 못 하는 경우 0 반환
*/
int fodfs(int v, int t, int f) {
	if (v == t) return f;

	visited[v] = 1;
	for (Edge& e : graph[v]) {
		if (visited[e.to]) continue;

		if (e.cap == 0) continue; // 실제로 존재하지 않는 간선

		int flow = fodfs(e.to, t, min(f, e.cap));

		if (flow == 0) continue; // 다음 edge 탐색

		// flow
		e.cap -= flow;
		graph[e.to][e.rev].cap += flow; // index 주의!

		return flow; // 최소 용량 반환
	}

	return 0; // not found
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	int N, M; cin >> N >> M; // 소의 수 축사의 수

	graph = vector<vector<Edge>>(SINK + 1); // 0 ~ SINK(500)
	for (int n{1}; n <= N; ++n) {
		int S; cin >> S;

		int srcRev = static_cast<int>(graph[0].size());
		int fromRev = static_cast<int>(graph[n].size());
		// 0 -> 소
		graph[0].emplace_back(fromRev, 0, n, 1); // cap = 1
		graph[n].emplace_back(srcRev, n, 0, 0);

		for (int s{}; s < S; ++s) {
			int barn; cin >> barn; // 축사는 영어로 barn
			barn += barnStart;
			// 반대 방향은 생각할 필요 없음.
			int toRev = static_cast<int>(graph[barn].size());

			// 소 -> 축사
			fromRev = static_cast<int>(graph[n].size());
			graph[n].emplace_back(toRev, n, barn, 1); // capacity 아무거나줘도 상관 없음.
			graph[barn].emplace_back(fromRev, barn, n, 0);
		}
	}

	for (int m{ 1 }; m <= M; ++m) {
		int barn = m + barnStart;
		int toRev = static_cast<int>(graph[barn].size());
		int sinkRev = static_cast<int>(graph[SINK].size());

		// 축사 -> 목적지
		graph[barn].emplace_back(sinkRev, barn, SINK, 1); // cap = 1;
		graph[SINK].emplace_back(toRev, SINK, barn, 0);
	}

	int s{}, e{ SINK };
	int maxFlow{};

	while (1) {
		visited.reset();
		int flow = fodfs(s, e, INF);

		if (flow == 0) break;

		maxFlow += flow;
	}

	cout << maxFlow << '\n';

	return 0;
}