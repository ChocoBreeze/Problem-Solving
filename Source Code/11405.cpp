// Minimum Cost Maximum Flow 공부
// https://m.blog.naver.com/kks227/220810623254
// 서점에서 가지고 있는 책의 개수의 합과 사람들이 사려고 하는 책의 개수의 합은 같다. = 최대 유량
// adjacency list

#include <iostream>
#include <vector>
#include <queue>

using namespace std;
constinit const int INF = 1 << 30;
constinit const int SRC = 0;
constinit const int SINK = 201;
constinit const int HUMAN = 100;

// Src(0) - 서점들(1 ~ 100) - 사람들(101 ~ 200) - Sink(201)

struct Edge {
	int rev, from, to, cap, cost;
	Edge(int rev, int from, int to, int cap, int cost) : rev(rev), from(from), to(to), cap(cap), cost(cost) {}
};
vector<vector<Edge>> graph;

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	int N, M;
	cin >> N >> M; // 사람의 수, 온라인 서점의 수

	vector<int> A(N + 1, 0), B(M + 1, 0);
	vector<vector<int>> C(M + 1, vector<int>(N + 1, 0));
	graph = vector<vector<Edge>>(SINK + 1); // 1 ~ SINK

	for (int n{1}; n <= N;++n) { // 사람
		cin >> A[n];
		// 사람(n) - SINK 연결
		// cost = 0, cap = A[n];
		int idx = n + HUMAN;
		int pRev = static_cast<int>(graph[idx].size());
		int sinkRev = static_cast<int>(graph[SINK].size());
		graph[idx].emplace_back(sinkRev, idx, SINK, A[n], 0); // cap = A[n], cost = 0
		graph[SINK].emplace_back(pRev, SINK, idx, 0, 0); // cap = 0, cost = 0
	}
	for (int m{1}; m <= M; ++m) { // 서점
		cin >> B[m];
		// SRC - 서점(m) 연결
		// cost = 0, cap = B[m];
		int srcRev = static_cast<int>(graph[SRC].size());
		int bsRev = static_cast<int>(graph[m].size());
		graph[SRC].emplace_back(bsRev, SRC, m, B[m], 0); // cap = B[m], cost = 0
		graph[m].emplace_back(srcRev, m, SRC, 0, 0); // cap = 0, cost = 0
	}
	for (int m{1}; m <= M;++m) { // 서점
		for (int n{1}; n <= N;++n) { // 사람
			cin >> C[m][n];
			// 서점(m)과 사람(n) 연결
			// cost = C[m][n], cap = 0
			int idx = n + HUMAN;
			int pRev = static_cast<int>(graph[idx].size());
			int bsRev = static_cast<int>(graph[m].size());
			graph[m].emplace_back(pRev, m, idx, INF, C[m][n]); // cap = INF(1이상), cost = C[m][n]
			graph[idx].emplace_back(bsRev, idx, m, 0, -C[m][n]); // cap = 0, cost = -C[m][n];
		}
	}

	int answer{};

	while (1) { // MCMF
		vector<int> prev(SINK + 1, -1);
		vector<int> prevIndex(SINK + 1, -1); // edge Index 저장
		vector<int> dist(SINK + 1, INF);
		vector<bool> inQ(SINK + 1, 0); // 해당 정점이 큐 안에 있는지 확인
		queue<int> q;
		q.push(SRC);
		dist[SRC] = 0;
		inQ[SRC] = true;

		while (!q.empty()) {
			int now = q.front(); q.pop();
			inQ[now] = false; // Q에서 꺼냄
			int index{};
			for (Edge& e : graph[now]) {
				// 최단 경로를 찾는 중이지만, 여전히 여유 용량 있어야 함
				if (e.cap > 0 && dist[e.to] > dist[now] + e.cost) {
					dist[e.to] = dist[now] + e.cost;
					prev[e.to] = now;
					prevIndex[e.to] = index;
					if (!inQ[e.to]) { // 큐에 없다면 큐에 넣기
						q.push(e.to);
						inQ[e.to] = true;
					}
				}
				++index;
			}
			
		}
		if (prev[SINK] == -1) break;

		int flow{INF};
		for (int i = SINK; i != SRC; i = prev[i]) { // 최대 흘릴 수 있는 flow 사용
			flow = min(flow, graph[prev[i]][prevIndex[i]].cap);
		}
		for (int i = SINK; i != SRC; i = prev[i]) { // 경로상의 모든 간선에 flow만큼의 유량을 흘림
			Edge& e = graph[prev[i]][prevIndex[i]];
			answer += flow * e.cost; // 총 비용이 각 간선 비용만큼 증가
			e.cap -= flow;
			graph[e.to][e.rev].cap += flow;
		}
	}
	cout << answer << '\n';
	return 0;
}