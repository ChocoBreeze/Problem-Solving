// https://www.acmicpc.net/problem/17412 +
// �̶� �� �� �湮�ߴ� ����(1, 2�� ���� ����)�� �� �� �̻� �湮���� ������ �Ѵ�.

// ���� ���ø� �� �� �湮���� �ʱ� ���ؼ� ������ 1������ ������ 2���� ������
// 2���� ���� ���� ���̿� �뷮�� 1�� �����ϱ�!
// ������ 4������ 4a�� 4b���� �����. 4a -> 4b�� ����
// 4a���� ������ ����, 4b���� ������ �������� ����

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

constinit const int INF = 1 << 30;

struct Edge {
	int rev, from, to, cap;
	Edge(int rev, int from, int to, int cap) : rev(rev), from(from), to(to), cap(cap) {}
};

vector<vector<Edge>> graph;
vector<int> visited;

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	int N, P;
	cin >> N >> P; // N���� ���ð� P���� ����� ��� ����Ǿ� �ִ�.

	const int SIZE = (N << 1) + 1; // 1 << N�� �ƴ�..
	graph = vector<vector<Edge>>(SIZE);
	for (int n{ 1 }; n <= N; ++n) { // 1 ~ N
		int na = (n << 1) - 1, nb = (n << 1);
		int fromRev = static_cast<int>(graph[na].size());
		int toRev = static_cast<int>(graph[nb].size());
		graph[na].emplace_back(toRev, na, nb, 1);
		graph[nb].emplace_back(fromRev, nb, na, 0);
	}

	for (int p{}; p < P; ++p) {
		int f, t;
		cin >> f >> t; // a - b (����� ��)
		// 1 -> 1, 2
		// 2 -> 3, 4
		int fa{ 2 * f - 1 }, fb{ 2 * f }, ta{ 2 * t - 1 }, tb{ 2 * t };
		// fb -> ta
		int taRev = static_cast<int>(graph[ta].size());
		int fbRev = static_cast<int>(graph[fb].size());
		graph[fb].emplace_back(taRev, fb, ta, 100); // cap ��� ����
		graph[ta].emplace_back(fbRev, ta, fb, 0); // ���� �������� �ʴ� ������ ����

		// tb -> fa
		int faRev = static_cast<int>(graph[fa].size());
		int tbRev = static_cast<int>(graph[tb].size());
		graph[tb].emplace_back(faRev, tb, fa, 100); // cap ��� ����
		graph[fa].emplace_back(tbRev, fa, tb, 0); // ���� �������� �ʴ� ������ ����
	}

	int maxFlow{}, src{ 2 }, sink{ 3 };
	// src 1 -> 2 (1�� ���� �� �ִ� ���� = 2)
	// sink 2 -> 3 (2�� ���� �� �ִ� ���� = 3)
	while (1) {
		visited.assign(SIZE, -1);
		vector<pair<int, int>> path(SIZE);
		
		queue<int> Q;
		Q.push(src);

		while (!Q.empty() && visited[sink] == -1) {
			int now = Q.front(); Q.pop();
			int index{};
			for (Edge& edg : graph[now]) {
				if (edg.cap > 0 && visited[edg.to] == -1) {
					Q.push(edg.to);
					visited[edg.to] = now;
					path[edg.to] = make_pair(now, index);
					if (edg.to == sink) break; // ����
				}
				++index;
			}
		}

		if (visited[sink] == -1) break;

		int flow = INF;
		for (int i{ sink }; i != src; i = visited[i]) { // �ּ� flow ����
			Edge& e = graph[path[i].first][path[i].second];
			flow = min(flow, e.cap);
		}
		for (int i{ sink }; i != src; i = visited[i]) { // flow �긮��
			Edge& e = graph[path[i].first][path[i].second];
			e.cap -= flow;
			graph[e.to][e.rev].cap += flow;
		}
		maxFlow += flow;
	}

	cout << maxFlow << '\n';


	return 0;
}