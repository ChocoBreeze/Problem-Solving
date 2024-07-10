// Minimum Cost Maximum Flow ����
// https://m.blog.naver.com/kks227/220810623254
// �������� ������ �ִ� å�� ������ �հ� ������� ����� �ϴ� å�� ������ ���� ����. = �ִ� ����
// adjacency list

#include <iostream>
#include <vector>
#include <queue>

using namespace std;
constinit const int INF = 1 << 30;
constinit const int SRC = 0;
constinit const int SINK = 201;
constinit const int HUMAN = 100;

// Src(0) - ������(1 ~ 100) - �����(101 ~ 200) - Sink(201)

struct Edge {
	int rev, from, to, cap, cost;
	Edge(int rev, int from, int to, int cap, int cost) : rev(rev), from(from), to(to), cap(cap), cost(cost) {}
};
vector<vector<Edge>> graph;

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	int N, M;
	cin >> N >> M; // ����� ��, �¶��� ������ ��

	vector<int> A(N + 1, 0), B(M + 1, 0);
	vector<vector<int>> C(M + 1, vector<int>(N + 1, 0));
	graph = vector<vector<Edge>>(SINK + 1); // 1 ~ SINK

	for (int n{1}; n <= N;++n) { // ���
		cin >> A[n];
		// ���(n) - SINK ����
		// cost = 0, cap = A[n];
		int idx = n + HUMAN;
		int pRev = static_cast<int>(graph[idx].size());
		int sinkRev = static_cast<int>(graph[SINK].size());
		graph[idx].emplace_back(sinkRev, idx, SINK, A[n], 0); // cap = A[n], cost = 0
		graph[SINK].emplace_back(pRev, SINK, idx, 0, 0); // cap = 0, cost = 0
	}
	for (int m{1}; m <= M; ++m) { // ����
		cin >> B[m];
		// SRC - ����(m) ����
		// cost = 0, cap = B[m];
		int srcRev = static_cast<int>(graph[SRC].size());
		int bsRev = static_cast<int>(graph[m].size());
		graph[SRC].emplace_back(bsRev, SRC, m, B[m], 0); // cap = B[m], cost = 0
		graph[m].emplace_back(srcRev, m, SRC, 0, 0); // cap = 0, cost = 0
	}
	for (int m{1}; m <= M;++m) { // ����
		for (int n{1}; n <= N;++n) { // ���
			cin >> C[m][n];
			// ����(m)�� ���(n) ����
			// cost = C[m][n], cap = 0
			int idx = n + HUMAN;
			int pRev = static_cast<int>(graph[idx].size());
			int bsRev = static_cast<int>(graph[m].size());
			graph[m].emplace_back(pRev, m, idx, INF, C[m][n]); // cap = INF(1�̻�), cost = C[m][n]
			graph[idx].emplace_back(bsRev, idx, m, 0, -C[m][n]); // cap = 0, cost = -C[m][n];
		}
	}

	int answer{};

	while (1) { // MCMF
		vector<int> prev(SINK + 1, -1);
		vector<int> prevIndex(SINK + 1, -1); // edge Index ����
		vector<int> dist(SINK + 1, INF);
		vector<bool> inQ(SINK + 1, 0); // �ش� ������ ť �ȿ� �ִ��� Ȯ��
		queue<int> q;
		q.push(SRC);
		dist[SRC] = 0;
		inQ[SRC] = true;

		while (!q.empty()) {
			int now = q.front(); q.pop();
			inQ[now] = false; // Q���� ����
			int index{};
			for (Edge& e : graph[now]) {
				// �ִ� ��θ� ã�� ��������, ������ ���� �뷮 �־�� ��
				if (e.cap > 0 && dist[e.to] > dist[now] + e.cost) {
					dist[e.to] = dist[now] + e.cost;
					prev[e.to] = now;
					prevIndex[e.to] = index;
					if (!inQ[e.to]) { // ť�� ���ٸ� ť�� �ֱ�
						q.push(e.to);
						inQ[e.to] = true;
					}
				}
				++index;
			}
			
		}
		if (prev[SINK] == -1) break;

		int flow{INF};
		for (int i = SINK; i != SRC; i = prev[i]) { // �ִ� �긱 �� �ִ� flow ���
			flow = min(flow, graph[prev[i]][prevIndex[i]].cap);
		}
		for (int i = SINK; i != SRC; i = prev[i]) { // ��λ��� ��� ������ flow��ŭ�� ������ �긲
			Edge& e = graph[prev[i]][prevIndex[i]];
			answer += flow * e.cost; // �� ����� �� ���� ��븸ŭ ����
			e.cap -= flow;
			graph[e.to][e.rev].cap += flow;
		}
	}
	cout << answer << '\n';
	return 0;
}