// edmonds-karp
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

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
	int N, P; cin >> N >> P;

	/*
	P���� �ܹ��� ��� ����
	1 -> 2������ ���� ���� �ٸ� ��� ã��
	�̶� �� ��ο� ���Ե� ���� �ٸ� ��ο� ���ԵǸ� �ȵȴ�. => cap = 1
	*/
	const int SIZE = N + 1;
	graph = vector<vector<Edge>>(SIZE); // 1 ~ N
	for (int p{}; p < P; ++p) {
		int from, to; cin >> from >> to;
		int fromRev = static_cast<int>(graph[from].size());
		int toRev = static_cast<int>(graph[to].size());
		graph[from].emplace_back(toRev, from, to, 1); // ��¥ ����
		graph[to].emplace_back(fromRev, to, from, 0); // ��¥ ����
	}

	int s{ 1 }, e{ 2 }, maxFlow{};

	while (1) {
		visited.assign(SIZE, -1); // �湮Ȯ�� �� ��𿡼� �Դ��� ����
		vector<pair<int, int>> path(SIZE); // ��λ��� �������� �����صξ� ���߿� ����
		// path[i] : Edge e�� to�� i�� ������ {from, index} ����
		// index(path[i].second) : from -> i(to)�� ������ from�� �� ��° index����.

		queue<int> Q;
		Q.push(s);

		while (!Q.empty() && visited[e] == -1) {
			int now = Q.front(); Q.pop();
			int index{};
			for (Edge& edg: graph[now]) {
				if (edg.cap > 0 && visited[edg.to] == -1) {
					Q.push(edg.to);
					visited[edg.to] = now;
					path[edg.to] = make_pair(now, index);
					if (edg.to == e) break; // ����
				}
				++index;
			}
		}
		if (visited[e] == -1) break;
		
		int flow = INF;
		for (int i{ e }; i != s; i = visited[i]) { // �ּ� flow ����
			Edge& e = graph[path[i].first][path[i].second];
			flow = min(flow, e.cap);
		}
		for (int i{ e }; i != s; i = visited[i]) { // flow �긮��
			Edge& e = graph[path[i].first][path[i].second];
			e.cap -= flow;
			graph[e.to][e.rev].cap += flow;
		}
		maxFlow += flow;
	}
	cout << maxFlow << '\n';

	return 0;
}