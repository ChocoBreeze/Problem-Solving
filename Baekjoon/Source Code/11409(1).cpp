// �ִ� ���.
// MCMF => cost�� ������ �ؼ� �ּ� cost ��� �� �������� �ٽ� ����
// adjacency matrix

#include <iostream>
#include <vector>
#include <queue>
#include <bitset>
#include <algorithm>

using namespace std;

// SRC(0) -> ������(1~400) -> ��(401~800) -> SINK(801)
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
	int N, M; // ����(~400)�� �� ��(~400)
	cin >> N >> M;
	// �� ������ �� ���� �ϸ� �� �� �ְ�, => cap = 1 (SRC -> ����)
	// ������ ���� ����ϴ� ����� 1���̾�� ��. => cap = 1(�� -> SINK)

	vector<vector<int>> graph(SIZE);
	for (int m{ 1 + WORK }; m <= M + WORK; ++m) {
		// �� ��(m) - SINK ����
		cap[m][SINK] = 1;
		// cap[SINK][m] = 0;
		graph[SINK].push_back(m);
		graph[m].push_back(SINK);
	}

	for (int n{ 1 }; n <= N; ++n) {
		cap[SRC][n] = 1; // SRC - ����(n) ���� (cap = 1)
		// cap[n][SRC] = 0;
		graph[SRC].push_back(n);
		graph[n].push_back(SRC);
		int workCnt{}; // �� �� �ִ� ���� ����
		cin >> workCnt;
		while (workCnt--) {
			int idx, pay;
			cin >> idx >> pay; // ���� ��ȣ�� ���� �� �� �����ؾ� �ϴ� ���� - cost
			idx += WORK;
			// ���� - �� ����
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
			inQ[curr] = 0; // �̰� ������.
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

		// ���� maxFlow��� ���� �� ���ص� �ִ� flow�� 1�� ���� �� �� �ִ�.
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