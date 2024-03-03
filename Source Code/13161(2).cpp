// Minimum Cut = Maximum Flow
// Maximum Flow - Dinic(O(V^2E))
// https://m.blog.naver.com/kks227/220812858041
// https://blog.naver.com/jinhan814/222284335708
// Adjacency List(188ms)

/*
level graph : 모든 정점에 대해 소스에서부터의 최단거리(거쳐야 하는 간선 개수)를 레벨 값으로 매겨놓은 그래프
- src(0)을 기준으로 인접한 정점들(1), 그와 인접한 정점들(2), ...
- 여유 용량(residual)이 없는 간선은 사용할 수 없다.
blocking flow : 레벨 그래프에서는 원래의 그래프에서 간선 (u, v)가 존재하더라도, v의 레벨이 u의 레벨보다 정확히 1 클 때만 이동 가능하다.
- 즉, 항상 인접하면서 자신보다 레벨이 1 큰 정점으로만 이동 가능하다.
- 이런 그래프에서 더 이상 소스에서 싱크로 흘릴 수 있는 유량이 없게 만드는 유량 상태.

(1) 레벨 그래프 만들기 - 이 때 싱크에 도달할 수 없다면 종료
(2) 레벨 그래프에서 blocking flow를 찾아 그만큼을 총 유량에 더하고 (1)로 돌아가기
*/

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

constinit const int MAXN = 500;
constinit const int SRC = 0;
constinit const int SINK = MAXN + 1;
constinit const int SIZE = SINK + 1; // 0 ~ SINK
constinit const int INF = 1'000'000'000;
// 사람들 index : 1 ~ 500(MAXN)
// SRC(0) - 1팀 사람들 - 2팀 사람들 - SINK(MAXN + 1)

struct Edge {
	int rev, from, to, cap;
	Edge(int rev, int from, int to, int cap) : rev(rev), from(from), to(to), cap(cap) {}
};

int N;
vector<vector<Edge>> graph;
vector<int> level, work;
// level : 레벨 그래프에서 정점의 레벨(SRC가 0)
// work : dfs 중, 이 정점이 몇 번째 간선까지 탐색했는지 기억하는 용도

// Dinic 전용 bfs 함수 => 레벨 그래프 구축
bool bfs() {
	fill(begin(level), end(level), -1);
	level[SRC] = 0;

	queue<int> q;
	q.push(SRC);
	while (!q.empty()) {
		int curr = q.front(); q.pop();
		for (auto& [rev, from, to, cap] : graph[curr]) {
			// 레벨 값이 설정되지 않았고, 간선에 residual이 있을 때만 이동
			if (level[to] == -1 && cap > 0) {
				level[to] = level[curr] + 1; // to의 레벨은 curr의 레벨 + 1
				q.push(to);
			}
		}
	}
	// SINK에 도달 가능하면 true 아니면 false
	return (level[SINK] != -1);
}

// Dinic 전용 dfs 함수 => curr에서 dest까지 최대 f만큼의 유량을 보낼 것
int dfs(int curr, int dest, int f) {
	if (curr == dest) return f; // base case: dest에 도달함

	// 현재 정점에서 인접한 정점들을 탐색
	// 이때, 이번 단계에서 이미 쓸모없다고 판단한 간선은 다시 볼 필요가 없으므로
	// work 배열로 간선 인덱스를 저장해 둠
	for (int& i = work[curr]; i < static_cast<int>(graph[curr].size()); ++i) {
		auto& [rev, from, to, cap] = graph[curr][i];
		// to의 레벨이 curr의 레벨 + 1이고, 간선에 residual이 남아 있어야만 이동
		if (level[to] == level[curr] + 1 && cap > 0) {
			// df : flow와 다음 dfs 함수의 결과 중 최솟값
			// 결과적으로 경로상의 간선들 중 가장 작은 residual이 됨
			int df = dfs(to, dest, min(cap, f));

			if (df > 0) { // augmenting path가 있다면, df 만큼 유량 흘리기
				graph[curr][i].cap -= df;
				graph[graph[curr][i].to][graph[curr][i].rev].cap += df;
				return df;
			}
		}
	}
	return 0; // 증가 경로를 찾지 못함 - 유량 0 흘리기
}

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int N{}; cin >> N;

	graph = vector<vector<Edge>>(SIZE);
	level = vector<int>(SIZE, -1);
	work = vector<int>(SIZE, 0);

	for (int n{1}; n <= N; ++n) {
		int t{}; cin >> t;
		// team이 정해진 경우
		if (t == 1) {
			int srcRev = static_cast<int>(graph[SRC].size());
			int nRev = static_cast<int>(graph[n].size());
			graph[SRC].emplace_back(nRev, SRC, n, INF); // SRC -> n (cap = INF)
			graph[n].emplace_back(srcRev, n, SRC, 0); // n -> SRC (cap = 0)
		}
		else if (t == 2) {
			int sinkRev = static_cast<int>(graph[SINK].size());
			int nRev = static_cast<int>(graph[n].size());
			graph[n].emplace_back(sinkRev, n, SINK, INF); // n -> SINK (cap = INF)
			graph[SINK].emplace_back(nRev, SINK, n, 0); // SINK -> n (cap = 0)
		}
	}
	for (int i{1}; i <= N; ++i) {
		for (int j{1}; j <= N; ++j) {
			int cap{}; cin >> cap;
			if (cap == 0) continue; // 이 부분 주석 시 188ms -> 632ms
			if (i < j) { // bidirectional
				int iRev = static_cast<int>(graph[i].size());
				int jRev = static_cast<int>(graph[j].size());
				graph[i].emplace_back(jRev, i, j, cap); // i -> j (cap = cap)
				graph[j].emplace_back(iRev, j, i, cap); // j -> i (cap = cap)
			}
		}
	}

	// Dinic
	int totalFlow{};
	// 레벨 그래프를 구축하여 싱크가 도달 가능한 동안 반복
	while (bfs()) {
		fill(begin(work), end(work), 0);
		// blocking flow 구하기
		while (1) {
			int f = dfs(SRC, SINK, INF); // dfs를 사용해 경로 찾기
			if (f == 0) break; // 더 이상 경로가 없음.
			totalFlow += f; // 총 유량에 이번에 구한 유량 더하기
		}
	}
	cout << totalFlow << '\n';
	// 최대 유량만 구한다면 여기서 끝.

	// 각 진영에 속한 사람을 판단하기 위해 소스에서의 도달 가능성 판별
	vector<bool> visited(SIZE, false);
	visited[SRC] = true;
	queue<int> q;
	q.push(SRC);
	while (!q.empty()) {
		int curr = q.front(); q.pop();
		for (auto& [rev, from, to, cap] : graph[curr]) {
			if (!visited[to] && cap > 0) { // 여유 용량이 남아 있는 간선만을 이용
				visited[to] = true;
				q.push(to);
			}
		}
	}

	// A 진영에 속한 사람들 : SRC에서 도달 가능
	// B 진영에 속한 사람들 : SRC에서 도달 불가능
	vector<int> groupA, groupB;
	groupA.reserve(N), groupB.reserve(N);
	for (int n{1}; n <= N; ++n) {
		if (visited[n]) groupA.push_back(n);
		else groupB.push_back(n);
	}

	for (int& p : groupA) cout << p << ' ';
	cout << '\n';
	for (int& p : groupB) cout << p << ' ';
	cout << '\n';

	return 0;
}