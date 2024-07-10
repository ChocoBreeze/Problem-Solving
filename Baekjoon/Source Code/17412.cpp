// ford-fulkerson
#include <iostream>
#include <vector>

using namespace std;

constinit const int INF = 1 << 30;
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
		visited.assign(SIZE, 0);

		int flow = fodfs(s, e, INF);

		if (flow == 0) break;

		maxFlow += flow;
	}
	cout << maxFlow << '\n';

	return 0;
}