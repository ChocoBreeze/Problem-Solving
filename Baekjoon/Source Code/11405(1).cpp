// Minimum Cost Maximum Flow ����
// https://m.blog.naver.com/kks227/220810623254
// �������� ������ �ִ� å�� ������ �հ� ������� ����� �ϴ� å�� ������ ���� ����. = �ִ� ����
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

// Src(0) - ������(1 ~ 100) - �����(101 ~ 200) - Sink(201)

vector<vector<int>> graph; // ���� ����

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	int N, M;
	cin >> N >> M; // ����� ��, �¶��� ������ ��

	graph = vector<vector<int>>(SIZE); // 1 ~ SINK
	int cap[SIZE][SIZE]{};
	int cost[SIZE][SIZE]{};
	int flow[SIZE][SIZE]{};

	for (int n{1 + HUMAN}; n <= N + HUMAN;++n) { // ���
		cin >> cap[n][SINK]; // ���(n) - SINK ����
		graph[SINK].push_back(n);
		graph[n].push_back(SINK);
	}
	for (int m{1}; m <= M; ++m) { // ����
		cin >> cap[SRC][m]; // SRC - ����(m) ����
		graph[SRC].push_back(m);
		graph[m].push_back(SRC);
	}
	for (int m{1}; m <= M;++m) { // ����
		for (int n{1 + HUMAN}; n <= N + HUMAN;++n) { // ���
			cin >> cost[m][n]; // ����(m)�� ���(n) ����
			cost[n][m] = -cost[m][n]; // ������ ������ ��� = �������� -1��
			cap[m][n] = INF; // ������ ������ �뷮�� 1 �̻�
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
			inQ[curr] = false; // Q���� ����
			for (int& next : graph[curr]) {
				// �ִ� ��θ� ã�� ��������, ������ ���� �뷮 �־�� ��
				if (cap[curr][next] - flow[curr][next] > 0 && dist[next] > dist[curr] + cost[curr][next]) {
					dist[next] = dist[curr] + cost[curr][next];
					prev[next] = curr;
					if (!inQ[next]) { // ť�� ���ٸ� ť�� �ֱ�
						q.push(next);
						inQ[next] = true;
					}
				}
			}
		}

		if (prev[SINK] == -1) break; // �� �̻� ��ΰ� ���ٸ� ���� Ż��

		int maxFlow{INF};
		for (int i = SINK; i != SRC; i = prev[i]) { // �ִ� �긱 �� �ִ� flow ���
			maxFlow = min(maxFlow, cap[prev[i]][i] - flow[prev[i]][i]);
		}
		for (int i = SINK; i != SRC; i = prev[i]) { // ��λ��� ��� ������ flow��ŭ�� ������ �긲
			answer += maxFlow * cost[prev[i]][i]; // �� ����� �� ���� ��븸ŭ ����
			flow[prev[i]][i] += maxFlow;
			flow[i][prev[i]] -= maxFlow;
		}
	}
	cout << answer << '\n';
	return 0;
}