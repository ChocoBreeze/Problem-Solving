// MCMF - Adjacency matrix
#include <iostream>
#include <vector>
#include <queue>

using namespace std;
constinit const int INF = 1 << 30;
constinit const int SRC = 0;
constinit const int SINK = 201;
constinit const int HUMAN = 100;
constinit const int SIZE = 202;
// SRC(0) - 서점(1~100) - 사람들(101~200) - SINK(201)

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int N{}, M{}; cin >> N >> M; // 사람, 서점
	
	vector graph(SIZE, vector<int>()); 
	vector cap(SIZE, vector<int>(SIZE, 0));
	vector cost(SIZE, vector<int>(SIZE, 0));
	vector flow(SIZE, vector<int>(SIZE, 0));

	// 각 사람이 사려고 하는 책의 개수 : A
	for (int n{}; n < N; ++n) { // 101 ~ 100 + n
		int p = HUMAN + n + 1;
		cin >> cap[p][SINK];
		graph[SINK].push_back(p);
		graph[p].push_back(SINK);
	}

	// 각 온라인 서점이 가지고 있는 책의 개수 : B
	for (int m{}; m < M; ++m) { // 1 ~ M
		int b = m + 1;
		cin >> cap[SRC][b];
		graph[b].push_back(SRC);
		graph[SRC].push_back(b);
	}

	// 각 온라인 서점이 각 사람들에게 책을 최대 몇 권 팔 수 있는지를 나타내는 C_{ij}
	for (int m{}; m < M; ++m) { // 서점
		int b = m + 1;
		for (int n{}; n < N; ++n) { // 사람
			int p = HUMAN + n + 1;
			cin >> cap[b][p]; // 역방향의 cap = 0
			graph[b].push_back(p);
			graph[p].push_back(b);
		}
	}

	// 각 온라인 서점이 각 사람들에게 책을 한 권 보내는데 필요한 배송비 D_{ij}
	for (int m{}; m < M; ++m) { // 서점
		int b = m + 1;
		for (int n{}; n < N; ++n) { // 사람
			int p = HUMAN + n + 1;
			cin >> cost[b][p];
			cost[p][b] = -cost[b][p]; // 역방향 간선의 비용 = 순방향의 -1배
		}
	}

	int maxBook{}, costSum{};

	while (1) { // MCMF
		vector<int> prev(SIZE, -1);
		vector<int> dist(SIZE, INF);
		vector<int> inQ(SIZE, 0); // bitset으로 바꾸기 가능
		queue<int> q; q.push(SRC);
		dist[SRC] = 0, inQ[SRC] = 1;

		while (!q.empty()) {
			int curr = q.front(); q.pop();
			inQ[curr] = false; // Q에서 꺼냄
			for (int& next : graph[curr]) {
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

		if (prev[SINK] == -1) break; // 더 이상 경로가 없다면 끝

		int maxFlow{ INF };
		for (int i = SINK; i != SRC; i = prev[i]) { // 최대 흘릴 수 있는 flow
			maxFlow = min(maxFlow, cap[prev[i]][i] - flow[prev[i]][i]);
		}
		for (int i = SINK; i != SRC; i = prev[i]) { // 경로상의 모든 간선에 flow만큼의 유량을 흘림
			costSum += maxFlow * cost[prev[i]][i]; 
			flow[prev[i]][i] += maxFlow;
			flow[i][prev[i]] -= maxFlow;
		}
		maxBook += maxFlow;
	}

	cout << maxBook << '\n' << costSum << '\n';
	return 0;
}