// MCMF
// https://www.acmicpc.net/problem/11405 �� ������ ����
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

struct Edge {
	int rev, from, to, cap, cost;
	Edge(int rev, int from, int to, int cap, int cost) : rev(rev), from(from), to(to), cap(cap), cost(cost) {}
};

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	int N, M; // ����(~400)�� �� ��(~400)
	cin >> N >> M;
	// �� ������ �� ���� �ϸ� �� �� �ְ�, => cap = 1 (SRC -> ����)
	// ������ ���� ����ϴ� ����� 1���̾�� ��. => cap = 1(�� -> SINK)

	vector<vector<Edge>> graph(SIZE);
	for (int m{ 1 + WORK }; m <= M + WORK; ++m) {
		// �� ��(m) - SINK ����
		int mRev = static_cast<int>(graph[m].size());
		int sinkRev = static_cast<int>(graph[SINK].size());
		graph[m].emplace_back(sinkRev, m, SINK, 1, 0); // cap = 1, cost = 0
		graph[SINK].emplace_back(mRev, SINK, m, 0, 0); // cap = 0, cost = 0
	}

	for (int n{1}; n <= N; ++n) {
		// SRC - ���(n) ����
		int srcRev = static_cast<int>(graph[SRC].size());
		int nRev = static_cast<int>(graph[n].size());
		graph[SRC].emplace_back(nRev, SRC, n, 1, 0); // cap = 1, cost = 0
		graph[n].emplace_back(srcRev, n, SRC, 0, 0); // cap = 0, cost = 0
		int workCnt{}; // �� �� �ִ� ���� ����
		cin >> workCnt;
		while (workCnt--) {
			int idx, pay;
			cin >> idx >> pay; // ���� ��ȣ�� ���� �� �� �����ؾ� �ϴ� ���� - cost
			idx += WORK;
			// ���(n) - ��(idx) ����
			int idxRev = static_cast<int>(graph[idx].size());
			int nRev = static_cast<int>(graph[n].size());
			graph[n].emplace_back(idxRev, n, idx, INF, pay); // cap = INF, cost = pay
			graph[idx].emplace_back(nRev, idx, n, 0, -pay); // cap = 0, cost = -pay
		}
	}

	int totalFlow{}, totalCost{};
	while (1) {
		vector<int> prev(SIZE, -1);
		vector<int> prevIndex(SIZE, -1); // edge index ����
		vector<int> dist(SIZE, INF);
		inQ.reset();
		queue<int> q;
		q.push(SRC);
		dist[SRC] = 0;
		inQ[SRC] = 1;

		while (!q.empty()) {
			int curr = q.front(); q.pop();
			inQ[curr] = 0; 
			int index{};
			for (Edge& e : graph[curr]) {
				int& next = e.to;
				if (e.cap > 0 && dist[next] > dist[curr] + e.cost) {
					dist[next] = dist[curr] + e.cost;
					prev[next] = curr;
					prevIndex[next] = index;
					if (!inQ[next]) {
						q.push(next);
						inQ[next] = 1;
					}
				}
				++index;
			}
		}

		if (prev[SINK] == -1) break;

		// ���� maxFlow��� ���� �� ���ص� �ִ� flow�� 1�� ���� �� �� �ִ�.
		for (int i{ SINK }; i != SRC; i = prev[i]) {
			Edge& e = graph[prev[i]][prevIndex[i]];
			totalCost += e.cost;
			--e.cap;
			++graph[e.to][e.rev].cap;
		}
		++totalFlow;
	}

	cout << totalFlow << '\n' << totalCost << '\n';
	return 0;
}