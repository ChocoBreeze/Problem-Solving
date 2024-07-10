// ����
// https://m.blog.naver.com/kks227/220804885235
// flow �׷����� �ٲٴ� �߻�.
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

// 0(source) -> �ҵ�(1 ~ N) -> ���(barnStart + M(1 ~ M)) -> ������(500)(sink)

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	int N, M; cin >> N >> M; // ���� �� ����� ��

	graph = vector<vector<Edge>>(SINK + 1); // 0 ~ SINK(500)
	for (int n{1}; n <= N; ++n) {
		int S; cin >> S;

		int srcRev = static_cast<int>(graph[0].size());
		int fromRev = static_cast<int>(graph[n].size());
		// 0 -> ��
		graph[0].emplace_back(fromRev, 0, n, 1); // cap = 1
		graph[n].emplace_back(srcRev, n, 0, 0);

		for (int s{}; s < S; ++s) {
			int barn; cin >> barn; // ���� ����� barn
			barn += barnStart;
			// �ݴ� ������ ������ �ʿ� ����.
			int toRev = static_cast<int>(graph[barn].size());

			// �� -> ���
			fromRev = static_cast<int>(graph[n].size());
			graph[n].emplace_back(toRev, n, barn, 1); // capacity �ƹ��ų��൵ ��� ����.
			graph[barn].emplace_back(fromRev, barn, n, 0);
		}
	}

	for (int m{ 1 }; m <= M; ++m) {
		int barn = m + barnStart;
		int toRev = static_cast<int>(graph[barn].size());
		int sinkRev = static_cast<int>(graph[SINK].size());

		// ��� -> ������
		graph[barn].emplace_back(sinkRev, barn, SINK, 1); // cap = 1;
		graph[SINK].emplace_back(toRev, SINK, barn, 0);
	}

	int s{}, e{ SINK };
	int maxFlow{};

	while (1) {
		vector<int>	prevVisited(SINK + 1, -1);
		vector<pair<int, int>> path(SINK + 1);
		// path[i] : Edge e�� to�� i�� ������ {from, index} ����
		// index : from -> i�� ������ from�� �� ��° index����.

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
					if (ed.to == e) break; // ����
				}
				++index;
			}
		}
		if (prevVisited[e] == -1) break; // ���� X(�� �̻� ���� ��ΰ� ����)

		int flow = INF;
		for (int i = e; i != s; i = prevVisited[i]) { // �ִ�� �긱 �� �ִ� �� ���ϱ�
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