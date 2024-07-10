// 공부
// https://m.blog.naver.com/kks227/220804885235
// flow 그래프로 바꾸는 발상.
// Edmonds-Karp
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

constinit const int SINK = 500;
constinit const int INF = 1 << 30;
constinit const int barnStart = 200;

struct Edge {
	int rev, from, to, cap;
	Edge(int r, int f, int t, int c) : rev(r), from(f), to(t), cap(c) {}
};

vector<vector<Edge>> graph;

// 0(source) -> 소들(1 ~ N) -> 축사(barnStart + M(1 ~ M)) -> 목적지(500)(sink)

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
		vector<int>	prevVisited(SINK + 1, -1);
		vector<pair<int, int>> path(SINK + 1);
		// path[i] : Edge e의 to가 i인 간선의 {from, index} 저장
		// index : from -> i의 간선이 from의 몇 번째 index인지.

		queue<int> Q;
		Q.push(s);

		while (!Q.empty() && prevVisited[e] == -1) {
			int now = Q.front(); Q.pop();
			int index{};
			for (Edge& ed : graph[now]) {
				if (ed.cap > 0 && prevVisited[ed.to] == -1) {
					Q.push(ed.to);
					prevVisited[ed.to] = now;
					path[ed.to] = make_pair(now, index);
					if (ed.to == e) break; // 도착
				}
				++index;
			}
		}
		if (prevVisited[e] == -1) break; // 도달 X(더 이상 증가 경로가 없음)

		int flow = INF;
		for (int i = e; i != s; i = prevVisited[i]) { // 최대로 흘릴 수 있는 양 구하기
			Edge& e = graph[path[i].first][path[i].second];
			flow = min(flow, e.cap);
		}
		for (int i = e; i != s; i = prevVisited[i]) {
			Edge& e = graph[path[i].first][path[i].second];
			e.cap -= flow;
			graph[e.to][e.rev].cap += flow;
		}
		maxFlow += flow;
	}

	cout << maxFlow << '\n';

	return 0;
}