// minimum cut
// �׷��� ������ ���·� �ٲٱ�
// �� �� �� ���� �ٽ� �� ����(���� ������ �ʰ�)
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;
constinit const int INF = 1 << 30;

struct Edge {
	int rev, from, to, cap;
	Edge(int rev, int from, int to, int cap) : rev(rev), from(from), to(to), cap(cap) {}
};

int N, M;
vector<vector<char>> Map;
vector<vector<Edge>> graph;
vector<int> visited;
pair<int, int> srcP, sinkP;

int fodfs(int v, int t, int f) {
	if (v == t) {
		return f;
	}

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
	cin >> N >> M;
	Map = vector<vector<char>>(N, vector<char>(M, 0));
	// [x][y] -> M * x + y
	// (M*x + y) * 2 -> (M*x + y) * 2 + 1
	const int VNUM{(N*M) << 1};
	graph = vector<vector<Edge>>(VNUM);

	for (int v{};v < N*M; ++v) {
		int from = (v << 1), to = (v << 1) + 1;
		int fromRev = static_cast<int>(graph[from].size());
		int toRev = static_cast<int>(graph[to].size());
		graph[from].emplace_back(toRev, from, to, 1); // �ѹ��� �湮�ϵ���
		graph[to].emplace_back(fromRev, to, from, 0);
	}

	for (int n{}; n < N; ++n) {
		for (int m{}; m < M; ++m) {
			cin >> Map[n][m];
		}
	}

	int src{}, sink{};
	for (int i{}; i < N; ++i) {
		for (int j{}; j < M; ++j) {

			if (Map[i][j] == '#') continue;
			for (int dir{}; dir < 4; ++dir) {
				int ni = i + "0211"[dir] - '1';
				int nj = j + "1102"[dir] - '1';
				if (ni < 0 || ni >= N || nj < 0 || nj >= M) continue;
				if (Map[ni][nj] == '#') continue;

				int from = ((i * M + j) << 1) + 1, to = (ni * M + nj) << 1;
				int fromRev = static_cast<int>(graph[from].size());
				int toRev = static_cast<int>(graph[to].size());
				graph[from].emplace_back(toRev, from, to, INF);  // cap ��� ����
				graph[to].emplace_back(fromRev, to, from, 0); // ���� �������� �ʴ� �����ε� �� cap�� 100�� �Z�� �̤�
			}

			if (Map[i][j] == 'K') {
				src = ((i * M + j) << 1) + 1;
				srcP = make_pair(i, j);
			}
			else if (Map[i][j] == 'H') {
				sink = ((i * M + j) << 1);
				sinkP = make_pair(i, j);
			}
		}
	}

	int srcIdx = src >> 1, sinkIdx = sink >> 1;
	// index�� ���ϸ� ���� [n][0]�̶� [n-1][M-1]�� -1�� ����..
	// ��ǥ�� ������
	// if (srcIdx + 1 == sinkIdx || srcIdx - 1 == sinkIdx || srcIdx + M == sinkIdx || srcIdx - M == sinkIdx)
	for (int dir{};dir<4;++dir) {
		int ni = srcP.first + "0211"[dir] - '1';
		int nj = srcP.second + "1102"[dir] - '1';
		if (ni == sinkP.first && nj == sinkP.second) {
			cout << "-1\n";
			return 0;
		}
	}

	int maxFlow{};
	while (1) {
		visited.assign(VNUM, 0);
		int flow = fodfs(src, sink, INF);
		if (flow == 0) break;
		maxFlow += flow;
	}
	
	cout << maxFlow << '\n';

	return 0;
}