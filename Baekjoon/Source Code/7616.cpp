// Dinic
// 당연히 그냥 bfs, dfs를 하는 과정에서 가는 정점들을 찍으면 원하는 정답이 안 나오는 것을 간과함.
// 5004KB, 44ms

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <string>
#include <sstream>

using namespace std;
// 0번 정점 버리고
constinit const int SRC = 2; // (1 << 1)
constinit const int SINK = 3; // (2 << 1) - 1
constinit const int INF = 1'000'000'000;

// 기존에 cap만 가지고 판별하는 경우, 실제로 흐르고 있는지 판별이 불가능함.
// flow 변수 추가(흐르는 양)
struct Edge {
	int rev, from, to, cap, flow;
	Edge(int rev, int from, int to, int cap, int flow) : rev(rev), from(from), to(to), cap(cap), flow(flow) {}
};
// 간선 연결 코드 중복이 많아서.. 함수화하면 좋을 듯
vector<vector<Edge>> graph;
vector<int> level, work;

bool bfs() { // level graph
	fill(begin(level), end(level), -1);
	level[SRC] = 0;

	queue<int> q;
	q.push(SRC);
	while (!q.empty()) {
		int curr = q.front(); q.pop();
		for (auto& [rev, from, to, cap, flow] : graph[curr]) {
			if (level[to] == -1 && cap - flow > 0) {
				level[to] = level[curr] + 1;
				q.push(to);
			}
		}
	}
	return (level[SINK] != -1); // SINK에 도달 가능하면 true 아니면 false
}

// curr에서 dest까지 최대 f만큼의 유량을 보낼 것
int dfs(int curr, int dest, int f) {
	if (curr == dest) return f;

	for (int& i = work[curr]; i < static_cast<int>(graph[curr].size()); ++i) {
		auto& [rev, from, to, cap, flow] = graph[curr][i];
		if (level[to] == level[curr] + 1 && cap - flow > 0) {
			int df = dfs(to, dest, min(cap - flow, f));

			if (df > 0) {
				graph[curr][i].flow += df;
				graph[graph[curr][i].to][graph[curr][i].rev].flow -= df;
				return df;
			}
		}
	}
	return 0; // 증가 경로를 찾지 못함 - 유량 0 흘리기
}

void PrintPath(int curr, int last = -1) {
	// cout << curr << ' ';
	if (last != ((curr + 1) >> 1)) {
		cout << ((curr + 1) >> 1) << ' ';
		last = (curr + 1) >> 1;
	}
	for (auto& [rev, from, to, cap, flow] : graph[curr]) {
		if (flow > 0) {
			--flow;
			PrintPath(to, last);
			break;
		}
	}
}

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	for (int tc{ 1 };; ++tc) {
		int K{}, N{}; cin >> K >> N; // 찾아야 할 경로 수, 교차로 수 N
		if (K == 0 && N == 0) break;

		const int SIZE = (N << 1) + 1;
		graph = vector<vector<Edge>>(SIZE);
		level = vector<int>(SIZE);
		work = vector<int>(SIZE);

		for (int n{ 1 }; n <= N; ++n) {
			// n * 2 - 1 ---- n * 2 연결 (cap = 1)
			int n1 = (n << 1) - 1, n2 = (n << 1);
			int n1Rev = static_cast<int>(graph[n1].size());
			int n2Rev = static_cast<int>(graph[n2].size());
			// rev, from, to, cap, flow
			graph[n1].emplace_back(n2Rev, n1, n2, 1, 0); // cap = 1
			graph[n2].emplace_back(n1Rev, n2, n1, 0, 0); // cap = 0

			string str, temp;
			while (str == "") getline(cin, str);
			istringstream iss(str);
			while (getline(iss, temp, ' ')) {
				int v = stoi(temp);
				int v1 = (v << 1) - 1;
				// k*2 - v*2-1 연결
				n2Rev = static_cast<int>(graph[n2].size());
				int v1Rev = static_cast<int>(graph[v1].size());
				graph[n2].emplace_back(v1Rev, n2, v1, 1, 0); // cap = 1
				graph[v1].emplace_back(n2Rev, v1, n2, 0, 0); // cap = 0
			}
		}

		// Dinic
		int totalFlow{};
		while (bfs()) { // 레벨 그래프를 구축하여 싱크가 도달 가능한 동안 반복
			fill(begin(work), end(work), 0);
			while (1) { // blocking flow 구하기
				int f = dfs(SRC, SINK, INF);
				if (f == 0) break;
				totalFlow += f; 
			}
		}
		// cout << totalFlow << '\n';
		cout << "Case " << tc << ":\n";
		if (totalFlow < K) cout << "Impossible\n";
		else {
			for (int k{}; k < K; ++k) {
				PrintPath(SRC);
				cout << '\n';
			}
		}
		cout << '\n';
	}
	return 0;
}