/*
�� ������ �뷮�� 1�ٸ� �ִ� ������ 1�� �پ��� ��� �� ������ ���� �߿��� �����̶�� �θ���.
1. �ִ� ���� �긮��
2. ��ȭ ���� �߿��� ���� �߿��� ���� ã�� (�뷮�� 1�پ��� �� �ִ� �뷮�� 1 �پ�� ��)

�ִ��� �기 ���¿��� -> ����(u,v)���� flow �긱 �� �ִ���(u -> v) Ȯ���ϱ�.
edmonds-karp
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

constinit const int INF = 1 << 30;

struct Edge {
	int rev, from, to, cap, ori; // ������ ������ �ε���, ����, ����, �뷮, ���� �������� ����
	Edge(int rev, int from, int to, int cap, int ori) : rev(rev), from(from), to(to), cap(cap), ori(ori) {}
};

vector<vector<Edge>> graph;
vector<Edge> edges;

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	int T; cin >> T;
	while (T--) {
		int N, M; cin >> N >> M; // ���� ��, ���� ��
		graph = vector<vector<Edge>>(N + 1); // 1(src) ~ N(sink)
		for (int m{}; m < M; ++m) {
			int f, t, b; cin >> f >> t >> b; // f -> t (cap = b)
			int fromRev = static_cast<int>(graph[f].size());
			int toRev = static_cast<int>(graph[t].size());
			graph[f].emplace_back(toRev, f, t, b, 1);
			graph[t].emplace_back(fromRev, t, f, 0, 0);
		}

		// 1. �ִ� ���� ���ϱ�
		int maxFlow{}, src{ 1 }, sink{ N };
		while (1) {
			vector<int> visited(N + 1, -1);
			vector<int> visitedIndex(N + 1, -1);

			queue<int> q;
			q.push(src);
			while (!q.empty() && visited[sink] == -1) {
				int now = q.front(); q.pop();
				int index{};
				for (Edge& e : graph[now]) {
					if (e.cap > 0 && visited[e.to] == -1) {
						q.push(e.to);
						visited[e.to] = now;
						visitedIndex[e.to] = index;
						if (e.to == sink) break;
					}
					++index;
				}
			}

			if (visited[sink] == -1) break;

			int flow{ INF };
			for (int i{ sink }; i != src; i = visited[i]) {
				flow = min(flow, graph[visited[i]][visitedIndex[i]].cap);
			}
			for (int i{ sink }; i != src; i = visited[i]) {
				Edge& e = graph[visited[i]][visitedIndex[i]];
				e.cap -= flow;
				graph[e.to][e.rev].cap += flow;
			}
			maxFlow += flow;
		}

		// 2. ��ȭ ���� �߿��� ���� �߿��� ���� ã�� (�뷮�� 1�پ��� �� �ִ� �뷮�� 1 �پ�� ��)
		// ���� �ڵ忡�� ������ ������ ����ϴ� ������ �־���.
		int answer{};
		for (vector<Edge>& row : graph) {
			for (Edge& e : row) {
				if (e.cap) continue; // ��ȭ ������
				if (!e.ori) continue; // ���� ������ ����
				int s{ e.from }, t{ e.to }; // s -> t �� �� �ִ��� Ȯ��
				queue<int> q;
				q.push(s);
				vector<int> visited(N + 1, -1);
				while (!q.empty() && visited[t] == -1) {
					int now = q.front(); q.pop();
					for (Edge& e : graph[now]) {
						if (e.cap > 0 && visited[e.to] == -1) {
							q.push(e.to);
							visited[e.to] = now;
							if (e.to == t) break;
						}
					}
				}
				if (visited[e.to] == -1) ++answer; // �ش� ������ �뷮�� �ϳ� �ٸ� �ִ� �뷮�� 1 �پ� ��
			}
		}
		cout << answer << '\n';
	}
	return 0;
}