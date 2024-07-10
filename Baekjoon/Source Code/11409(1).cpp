// 최대 비용.
// MCMF => cost를 음수로 해서 최소 cost 계산 후 마지막에 다시 반전
// adjacency matrix

#include <iostream>
#include <vector>
#include <queue>
#include <bitset>
#include <algorithm>

using namespace std;

// SRC(0) -> 직원들(1~400) -> 일(401~800) -> SINK(801)
constinit const int SRC = 0;
constinit const int WORK = 400;
constinit const int SINK = 801;
constinit const int SIZE = 802;
constinit const int INF = 1 << 30;
bitset<SIZE> inQ;

int cap[SIZE][SIZE]{};
int cost[SIZE][SIZE]{};
int flow[SIZE][SIZE]{};

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	int N, M; // 직원(~400)과 할 일(~400)
	cin >> N >> M;
	// 각 직원은 한 개의 일만 할 수 있고, => cap = 1 (SRC -> 직원)
	// 각각의 일을 담당하는 사람은 1명이어야 함. => cap = 1(일 -> SINK)

	vector<vector<int>> graph(SIZE);
	for (int m{ 1 + WORK }; m <= M + WORK; ++m) {
		// 할 일(m) - SINK 연결
		cap[m][SINK] = 1;
		// cap[SINK][m] = 0;
		graph[SINK].push_back(m);
		graph[m].push_back(SINK);
	}

	for (int n{ 1 }; n <= N; ++n) {
		cap[SRC][n] = 1; // SRC - 직원(n) 연결 (cap = 1)
		// cap[n][SRC] = 0;
		graph[SRC].push_back(n);
		graph[n].push_back(SRC);
		int workCnt{}; // 할 수 있는 일의 개수
		cin >> workCnt;
		while (workCnt--) {
			int idx, pay;
			cin >> idx >> pay; // 일의 번호와 일을 할 때 지급해야 하는 월급 - cost
			idx += WORK;
			// 직원 - 일 연결
			cost[n][idx] = -pay;
			cost[idx][n] = pay;
			cap[n][idx] = INF;
			// cap[idx][n] = 0;
			graph[n].push_back(idx);
			graph[idx].push_back(n);
		}
	}

	int totalFlow{}, totalCost{};
	while (1) {
		vector<int> prev(SIZE, -1);
		vector<int> dist(SIZE, INF);
		inQ.reset();
		queue<int> q;
		q.push(SRC);
		dist[SRC] = 0;
		inQ[SRC] = 1;
		while (!q.empty()) {
			int curr = q.front(); q.pop();
			inQ[curr] = 0; // 이거 빼먹음.
			for (int& next : graph[curr]) {
				if (cap[curr][next] - flow[curr][next] > 0 && dist[next] > dist[curr] + cost[curr][next]) {
					dist[next] = dist[curr] + cost[curr][next];
					prev[next] = curr;
					if (!inQ[next]) {
						q.push(next);
						inQ[next] = 1;
					}
				}
			}
		}

		if (prev[SINK] == -1) break;

		// 굳이 maxFlow라는 것을 안 구해도 최대 flow가 1인 것을 알 수 있다.
		for (int i{ SINK }; i != SRC; i = prev[i]) {
			totalCost += cost[prev[i]][i];
			flow[prev[i]][i]++;
			flow[i][prev[i]]--;
		}
		++totalFlow;
	}

	cout << totalFlow << '\n' << -totalCost << '\n';
	return 0;
}