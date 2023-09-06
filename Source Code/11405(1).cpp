// Minimum Cost Maximum Flow 공부
// https://m.blog.naver.com/kks227/220810623254
// 서점에서 가지고 있는 책의 개수의 합과 사람들이 사려고 하는 책의 개수의 합은 같다. = 최대 유량
// adjacency matrix

#include <iostream>
#include <vector>
#include <queue>
#include <bitset>

using namespace std;
constinit const int INF = 1 << 30;
constinit const int SRC = 0;
constinit const int SINK = 201;
constinit const int SIZE = 202;
constinit const int HUMAN = 100;
bitset<SIZE> inQ;

// Src(0) - 서점들(1 ~ 100) - 사람들(101 ~ 200) - Sink(201)

vector<vector<int>> graph; // 간선 연결

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	int N, M;
	cin >> N >> M; // 사람의 수, 온라인 서점의 수

	graph = vector<vector<int>>(SIZE); // 1 ~ SINK
	int cap[SIZE][SIZE]{};
	int cost[SIZE][SIZE]{};
	int flow[SIZE][SIZE]{};

	for (int n{1 + HUMAN}; n <= N + HUMAN;++n) { // 사람
		cin >> cap[n][SINK]; // 사람(n) - SINK 연결
		graph[SINK].push_back(n);
		graph[n].push_back(SINK);
	}
	for (int m{1}; m <= M; ++m) { // 서점
		cin >> cap[SRC][m]; // SRC - 서점(m) 연결
		graph[SRC].push_back(m);
		graph[m].push_back(SRC);
	}
	for (int m{1}; m <= M;++m) { // 서점
		for (int n{1 + HUMAN}; n <= N + HUMAN;++n) { // 사람
			cin >> cost[m][n]; // 서점(m)과 사람(n) 연결
			cost[n][m] = -cost[m][n]; // 역방향 간선의 비용 = 순방향의 -1배
			cap[m][n] = INF; // 순방향 간선의 용량이 1 이상
			graph[m].push_back(n);
			graph[n].push_back(m);
		}
	}

	int answer{};

	while (1) { // MCMF
		vector<int> prev(SIZE, -1);
		vector<int> dist(SIZE, INF);
		inQ.reset();
		queue<int> q;
		q.push(SRC);
		dist[SRC] = 0;
		inQ[SRC] = true;

		while (!q.empty()) {
			int curr = q.front(); q.pop();
			inQ[curr] = false; // Q에서 꺼냄
			for (int& next : graph[curr]) {
				// 최단 경로를 찾는 중이지만, 여전히 여유 용량 있어야 함
				if (cap[curr][next] - flow[curr][next] > 0 && dist[next] > dist[curr] + cost[curr][next]) {
					dist[next] = dist[curr] + cost[curr][next];
					prev[next] = curr;
					if (!inQ[next]) { // 큐에 없다면 큐에 넣기
						q.push(next);
						inQ[next] = true;
					}
				}
			}
		}

		if (prev[SINK] == -1) break; // 더 이상 경로가 없다면 루프 탈출

		int maxFlow{INF};
		for (int i = SINK; i != SRC; i = prev[i]) { // 최대 흘릴 수 있는 flow 사용
			maxFlow = min(maxFlow, cap[prev[i]][i] - flow[prev[i]][i]);
		}
		for (int i = SINK; i != SRC; i = prev[i]) { // 경로상의 모든 간선에 flow만큼의 유량을 흘림
			answer += maxFlow * cost[prev[i]][i]; // 총 비용이 각 간선 비용만큼 증가
			flow[prev[i]][i] += maxFlow;
			flow[i][prev[i]] -= maxFlow;
		}
	}
	cout << answer << '\n';
	return 0;
}