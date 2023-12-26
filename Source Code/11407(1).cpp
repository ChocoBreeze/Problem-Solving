// MCMF - Adjacency list
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

struct Edge {
	int rev, from, to, cap, cost;
	Edge(int rev, int from, int to, int cap, int cost) : rev(rev), from(from), to(to), cap(cap), cost(cost) {}
};

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int N{}, M{}; cin >> N >> M; // 사람, 서점
	
	vector graph(SIZE, vector<Edge>());

	// 각 사람이 사려고 하는 책의 개수 : A
	for (int n{}; n < N; ++n) { // 101 ~ 100 + n
		int cap{}; cin >> cap;
		int p = HUMAN + n + 1;
		int pRev = static_cast<int>(graph[p].size());
		int sinkRev = static_cast<int>(graph[SINK].size());
		graph[p].emplace_back(sinkRev, p, SINK, cap, 0); // cap = cap, cost = 0
		graph[SINK].emplace_back(pRev, SINK, p, 0, 0); // cap = 0, cost = 0
		
	}

	// 각 온라인 서점이 가지고 있는 책의 개수 : B
	for (int m{}; m < M; ++m) { // 1 ~ M
		int cap{}; cin >> cap;
		int b = m + 1;
		int srcRev = static_cast<int>(graph[SRC].size());
		int bRev = static_cast<int>(graph[b].size());
		graph[SRC].emplace_back(bRev, SRC, b, cap, 0); // cap = B[m], cost = 0
		graph[b].emplace_back(srcRev, b, SRC, 0, 0); // cap = 0, cost = 0
	}

	// 각 온라인 서점이 각 사람들에게 책을 최대 몇 권 팔 수 있는지를 나타내는 C_{ij}
	vector C(M, vector<int>(N, 0));
	for (int m{}; m < M; ++m) {
		for (int n{}; n < N; ++n) {
			cin >> C[m][n];
		}
	}
	// 각 온라인 서점이 각 사람들에게 책을 한 권 보내는데 필요한 배송비 D_{ij}
	vector D(M, vector<int>(N, 0));
	for (int m{}; m < M; ++m) { // 서점
		int b = m + 1;
		for (int n{}; n < N; ++n) { // 사람
			int p = HUMAN + n + 1;
			cin >> D[m][n];
			int& cap = C[m][n], & cost = D[m][n];
			int pRev = static_cast<int>(graph[p].size());
			int bRev = static_cast<int>(graph[b].size());
			graph[b].emplace_back(pRev, b, p, cap, cost);
			graph[p].emplace_back(bRev, p, b, 0, -cost); // 역방향 cap = 0, cost = -cost
		}
	}

	int maxBook{}, costSum{};
	while (1) { // MCMF
		vector<int> prev(SIZE, -1);
		vector<int> prevIndex(SINK + 1, -1); // edge Index 저장
		vector<int> dist(SIZE, INF);
		vector<int> inQ(SIZE, 0); // bitset으로 바꾸기 가능
		queue<int> q; q.push(SRC);
		dist[SRC] = 0, inQ[SRC] = 1;

		while (!q.empty()) {
			int curr = q.front(); q.pop();
			inQ[curr] = false; // Q에서 꺼냄
			int index{}; // 몇 번째 간선인지 저장
			for (auto& [rev, from, to, cap, cost] : graph[curr]) {
				if (cap > 0 && dist[to] > dist[curr] + cost) {
					dist[to] = dist[curr] + cost;
					prev[to] = curr, prevIndex[to] = index;
					if (!inQ[to]) { // 큐에 없다면 큐에 넣기
						q.push(to);
						inQ[to] = true;
					}
				}
				++index;
			}
		}

		if (prev[SINK] == -1) break; // 더 이상 경로가 없다면 끝

		int maxFlow{ INF };
		for (int i = SINK; i != SRC; i = prev[i]) { // 최대 흘릴 수 있는 flow
			maxFlow = min(maxFlow, graph[prev[i]][prevIndex[i]].cap);
		}
		for (int i = SINK; i != SRC; i = prev[i]) { // 경로상의 모든 간선에 flow만큼의 유량을 흘림
			Edge& e = graph[prev[i]][prevIndex[i]];
			costSum += maxFlow * e.cost;
			e.cap -= maxFlow; // 현재 간선
			graph[e.to][e.rev].cap += maxFlow; // 반대 간선
		}
		maxBook += maxFlow;
	}

	cout << maxBook << '\n' << costSum << '\n';
	return 0;
}