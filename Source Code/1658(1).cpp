// dinic
// https://www.crocus.co.kr/1067
// 같은 우리에 대한 키를 가지는 사람들을 연결
// 2176KB, 0ms

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;
constinit const int SRC{}, INF{ 1 << 30 }, PIG{ 100 }, SINK{ 1101 }, SIZE{ 1102 };
// SRC - 손님(1~100) - 돼지 우리(101~1100) - SINK : 1101

struct Edge {
	int rev, from, to, cap;
	Edge(int rev, int from, int to, int cap) : rev(rev), from(from), to(to), cap(cap) {}
};
vector<vector<Edge>> graph;
vector<int> level, work;

bool bfs() {
	fill(begin(level), end(level), -1);
	level[SRC] = 0;

	queue<int> q;
	q.push(SRC);
	while (!q.empty()) {
		int curr = q.front(); q.pop();
		for (auto& [rev, from, to, cap] : graph[curr]) {
			if (level[to] == -1 && cap > 0) {
				level[to] = level[curr] + 1;
				q.push(to);
			}
		}
	}
	return (level[SINK] != -1);
}

int dfs(int curr, int dest, int flow) {
	if (curr == dest) return flow;

	for (int& i = work[curr]; i < static_cast<int>(graph[curr].size()); ++i) {
		auto& [rev, from, to, cap] = graph[curr][i];
		if (level[to] == level[curr] + 1 && cap > 0) {
			int df = dfs(to, dest, min(cap, flow)); // df : flow와 다음 dfs 함수의 결과 중 최솟값

			if (df > 0) {
				graph[curr][i].cap -= df;
				graph[graph[curr][i].to][graph[curr][i].rev].cap += df;
				return df;
			}
		}
	}
	return 0;
}

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int M{}, N{}; cin >> M >> N; // 돼지 우리 수, 손님 수

	graph = vector<vector<Edge>>(SIZE);
	level.assign(SIZE, 0), work.assign(SIZE, 0);
	vector share(M + 1, vector<int>()); // share[m] : 우리 번호가 m인 열쇠를 갖고 있는 손님들.

	for (int m{ 1 + PIG }; m <= PIG + M; ++m) { // 1, 2, ... m
		int mm{}; cin >> mm;
		// 돼지 우리 -> SINK 간선 추가
		int mRev = static_cast<int>(graph[m].size());
		int sinkRev = static_cast<int>(graph[SINK].size());
		graph[m].emplace_back(sinkRev, m, SINK, mm); // cap = mm
		graph[SINK].emplace_back(mRev, SINK, m, 0); // cap = 0
	}

	for (int n{ 1 }; n <= N; ++n) { // 손님 index
		int A{}; cin >> A; // key 개수
		for (int a{}; a < A; ++a) {
			int val{}; cin >> val; // val번째 우리
			share[val].push_back(n);

			// n번 사람에서 -> 우리까지 가는 간선 추가
			int nRev = static_cast<int>(graph[n].size());
			int valRev = static_cast<int>(graph[PIG + val].size());
			graph[n].emplace_back(valRev, n, PIG + val, INF); // cap = INF
			graph[PIG + val].emplace_back(nRev, PIG + val, n, 0); // cap = 0
		}
		int B{}; cin >> B; // 손님이 사길 원하는 돼지 수
		// SRC -> 손님 간선 추가
		int srcRev = static_cast<int>(graph[SRC].size());
		int nRev = static_cast<int>(graph[n].size());
		graph[SRC].emplace_back(nRev, SRC, n, B); // cap = B
		graph[n].emplace_back(srcRev, n, SRC, 0); // cap = 0
	}

	// 같은 키를 가지는 손님끼리 연결
	for (int m{ 1 }; m <= M; ++m) { // 우리 index
		for (int i{}; i < static_cast<int>(share[m].size()); ++i) {
			int here{ share[m][i] }; // 손님 1 (먼저 온 손님)
			for (int j{ i + 1 }; j < static_cast<int>(share[m].size()); ++j) {
				int there{ share[m][j] }; // 손님 2 (나중에 온 손님)

				// 왜 there -> here로 가는 간선을 만들어 줘야 하지?
				// 나중에 또 같은 키로 문을 여는 사람이 있다면 그런 사람들에게 몰아줘야 함.
				// 미래에 들어올 수 있는 간선을 과거로 연결해야 하는 듯!
				int hereRev = static_cast<int>(graph[here].size());
				int thereRev = static_cast<int>(graph[there].size());
				graph[here].emplace_back(thereRev, here, there, 0);
				graph[there].emplace_back(hereRev, there, here, INF);
			}
		}
	}

	int total{};
	while (bfs()) { // level graph 
		fill(begin(work), end(work), 0);
		while (1) { // blocking flow
			int flow = dfs(SRC, SINK, INF);
			if (flow == 0) break; // 더 이상 경로가 없음.
			total += flow;
		}
	}
	cout << total << '\n';
	return 0;
}