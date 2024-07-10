// Edmonds-Karp
// https://www.acmicpc.net/problem/2188 �Ȱ���
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

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
	int N, M; cin >> N >> M; // ���� 1 ~ N, �� 1 ~ M
	const int WORKERNUM = N + 1;

	graph = vector<vector<Edge>>(SINK + 1);
	for (int n{1}; n <= N; ++n) {
		int S{}; cin >> S;

		// src -> worker
		int srcRev = static_cast<int>(graph[0].size());
		int fromRev = static_cast<int>(graph[n].size());
		graph[0].emplace_back(fromRev, 0, n, 1);
		graph[n].emplace_back(srcRev, n, 0, 0); // �ݴ� ������ ����

		for (int s{}; s < S; ++s) {
			int work; cin >> work;
			work += WORKERNUM;
			// worker -> work
			int toRev = static_cast<int>(graph[work].size());
			fromRev = static_cast<int>(graph[n].size());
			graph[n].emplace_back(toRev, n, work, 1); // capacity �ƹ��ų��൵ ��� ����.
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
		vector<int> prevVisited(SINK + 1, -1);
		vector<pair<int, int>> path(SINK + 1);
		// path[i] : Edge e�� to�� i�� ������ {from, index} ����
		// index : from -> i�� ������ from�� �� ��° index����.

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
					if (e.to == d) break; // �̰� ���̰� �ð� �����ΰ�?
				}
				++index;
			}
		}

		if (prevVisited[d] == -1) break;

		int flow = INF;
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