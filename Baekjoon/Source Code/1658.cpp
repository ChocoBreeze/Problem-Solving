// dinic
// adjacency list
// 그래프 구성이 까다로운..
// MLE
// 4908KB, 96ms
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;
constinit const int SRC = 0, INF = 1 << 30;

struct Edge {
	int rev, from, to, cap;
	Edge(int rev, int from, int to, int cap) : rev(rev), from(from), to(to), cap(cap) {}
};
vector<vector<Edge>> graph;
vector<int> level, work;

bool bfs(int SINK) {
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
	const int SINK = (N + 1) * (M + 1), SIZE = SINK + 1;

	graph = vector<vector<Edge>>(SIZE);
	level.assign(SIZE, 0), work.assign(SIZE, 0);

	// SRC -> 초기 우리
	for (int m{ 1 }; m <= M; ++m) { // 1, 2, ... m
		int mm{}; cin >> mm;
		int srcRev = static_cast<int>(graph[SRC].size());
		int mRev = static_cast<int>(graph[m].size());
		// rev, from, to, cap;
		graph[SRC].emplace_back(mRev, SRC, m, mm); // cap = mm
		graph[m].emplace_back(srcRev, m, SRC, 0); // cap = 0
	}

	int customerIdx{ (N + 1) * M + 1 }; // 손님 시작 index (이거 잘 못 잡았구나 ㅜㅠㅜㅠㅠㅠ)
	for (int n{ 1 }; n <= N; ++n, ++customerIdx) {
		for (int m{ 1 }; m <= M; ++m) { // 같은 우리끼리 연결
			int last{ m + (n - 1) * M }, now{ m + n * M };
			int lastRev = static_cast<int>(graph[last].size());
			int nowRev = static_cast<int>(graph[now].size());
			graph[last].emplace_back(nowRev, last, now, INF); // cap = INF
			graph[now].emplace_back(lastRev, now, last, 0); // cap = 0
		}
		int A{}; cin >> A; // 열쇠 개수
		vector<int> keys(A, 0);
		for (int& k : keys) {
			cin >> k;
			int now{ n * M + k };
			// 오늘 열린 우리와 손님 연결
			int nowRev = static_cast<int>(graph[now].size());
			int customerRev = static_cast<int>(graph[customerIdx].size());
			graph[now].emplace_back(customerRev, now, customerIdx, INF); // cap = INF
			graph[customerIdx].emplace_back(nowRev, customerIdx, now, 0); // cap = 0
		}
		if (n != N) { // 오늘 문 열린 우리와 내일 우리끼리 연결
			for (int i{}; i < A; ++i) { // A[i]
				for (int j{ i + 1 }; j < A; ++j) {
					int nowI{ n * M + keys[i] }, tomorrowI{ (n + 1) * M + keys[i] };
					int nowIRev = static_cast<int>(graph[nowI].size());
					int tomorrowIRev = static_cast<int>(graph[tomorrowI].size());

					int nowJ{ n * M + keys[j] }, tomorrowJ{ (n + 1) * M + keys[j] };
					int nowJRev = static_cast<int>(graph[nowJ].size());
					int tomorrowJRev = static_cast<int>(graph[tomorrowJ].size());

					graph[nowI].emplace_back(tomorrowJRev, nowI, tomorrowJ, INF);
					graph[tomorrowJ].emplace_back(nowIRev, tomorrowJ, nowI, 0);

					graph[nowJ].emplace_back(tomorrowIRev, nowJ, tomorrowI, INF);
					graph[tomorrowI].emplace_back(nowJRev, tomorrowI, nowJ, 0);
				}
			}
		}
		int B{}; cin >> B; // 손님이 사길 원하는 돼지 수
		// 손님과 SINK 연결
		int sinkRev = static_cast<int>(graph[SINK].size());
		int customerRev = static_cast<int>(graph[customerIdx].size());
		graph[customerIdx].emplace_back(sinkRev, customerIdx, SINK, B);
		graph[SINK].emplace_back(customerRev, SINK, customerIdx, 0);
	}

	int total{};
	while (bfs(SINK)) { // level graph 
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