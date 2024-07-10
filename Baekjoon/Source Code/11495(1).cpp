// Ford-Fulkerson
// �׷��� ���� idea : https://m.blog.naver.com/kks227/220804885235
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

constinit const int INF = 1 << 30;
// 50 * 50 -> max = 2499
constinit const int SRC = 2500;
constinit const int SINK = 2501;
constinit const int SIZE = 2510; // ���� �γ��ϰ�

struct Edge {
	int rev, from, to, cap;
	Edge(int rev, int from, int to, int cap) : rev(rev), from(from), to(to), cap(cap) {}
};

vector<vector<Edge>> graph;
vector<int> visited;
int fodfs(int v, int t, int f) {
	if (v == t) return f;
	visited[v] = 1;

	for (Edge& e : graph[v]) {
		if (visited[e.to]) continue;
		if (e.cap == 0) continue;
		int flow = fodfs(e.to, t, min(f, e.cap));
		if (flow == 0) continue;

		e.cap -= flow;
		graph[e.to][e.rev].cap += flow;
		return flow;
	}
	return 0;
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	int T{}; cin >> T;
	while (T--) {
		int n{}, m{}; cin >> n >> m; // ��, ��
		vector<vector<int>> matrix(n, vector<int>(m, 0));
		for (auto& row : matrix) {
			for (auto& v : row) {
				cin >> v;
			}
		}
		graph = vector<vector<Edge>>(SIZE);

		// 1. �׷��� �����
		int srcFlow{}, sinkFlow{}; // ���� SRC���� ������, SINK�� ���� �뷮
		for (int r{}; r < n; ++r) {
			for (int c{}; c < m; ++c) {
				int now = r + c;
				int nodeIndex = r * m + c;
				if ((now & 1) == 1) { // Ȧ�� -> SINK�� ����
					int nodeRev = static_cast<int>(graph[nodeIndex].size());
					int sinkRev = static_cast<int>(graph[SINK].size());
					graph[nodeIndex].emplace_back(sinkRev, nodeIndex, SINK, matrix[r][c]); // cap = matrix[r][c]
					graph[SINK].emplace_back(nodeRev, SINK, nodeIndex, 0); // cap = 0
					sinkFlow += matrix[r][c];
				}
				else {
					// ¦�� -> SRC�� ����
					int nodeRev = static_cast<int>(graph[nodeIndex].size());
					int srcRev = static_cast<int>(graph[SRC].size());
					graph[SRC].emplace_back(nodeRev, SRC, nodeIndex, matrix[r][c]); // cap = matrix[r][c]
					graph[nodeIndex].emplace_back(srcRev, nodeIndex, SRC, 0); // cap = 0
					srcFlow += matrix[r][c];

					// ¦�� -> Ȧ�� ����
					for (int d{}; d < 4; ++d) {
						int nr = r + "0211"[d] - '1';
						int nc = c + "1102"[d] - '1';
						if (nr < 0 || nc < 0 || nr >= n || nc >= m) continue;
						int nextIndex = nr * m + nc;
						nodeRev = static_cast<int>(graph[nodeIndex].size());
						int nextRev = static_cast<int>(graph[nextIndex].size());
						graph[nodeIndex].emplace_back(nextRev, nodeIndex, nextIndex, INF); // cap = INF
						graph[nextIndex].emplace_back(nodeRev, nextIndex, nodeIndex, 0); // cap = 0
					}
				}
			}
		}

		// 2. MaxFlow ���
		int maxFlow{};
		while (1) {
			visited = vector<int>(SIZE, 0);
			int flow = fodfs(SRC, SINK, INF);
			if (flow == 0) break;
			maxFlow += flow;
		}
		cout << srcFlow + sinkFlow - maxFlow << '\n';
		// (��� ���� �� - maxFlow)�ص� �ȴ�.
	}

	return 0;
}