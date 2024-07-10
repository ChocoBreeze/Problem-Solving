// Network Flow
// ����
// Ford-Fulkerson
// ���� �ذ���� ���̴� �˰���� �ڷᱸ�� å ����.

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

constinit const int INF = 1 << 30;
constinit const int SIZE = 52; // 0 ~ 51

// ABCD...Zabcd...z
inline int ToInt(char c) {
	if (c & ' ') return c - 'a' + 26;
	else return c - 'A';
}

struct Edge {
	// rev : (to, from)�� graph[to]���� �� ��° �������
	// cap : capacity
	int rev, from, to, cap;
	Edge(int rev, int from, int to, int cap) : rev(rev), from(from), to(to), cap(cap) {}
};

vector<vector<Edge>> graph; // adjacency list

// �ܿ� �׷��� ���� s-t�н��� ã��(dfs)
// ��ȯ���� s-t�н����� �뷮�� �ּڰ�(ã�� ���� ��� 0)
// f: s���� v�� �����ϴ� ������ �� �� �뷮�� �ּڰ�
vector<int> visited;
int fodfs(int v, int t, int f) { // ������Ŀ���̶� fodfs�� ��?
	// ���� t�� ���޽� ��ȯ
	if (v == t) return f;

	// DFS
	visited[v] = true;
	for (Edge& e : graph[v]) {
		if (visited[e.to]) continue;

		// �뷮 0�� edge�� ������ �������� ����. (������ ����)
		if (e.cap == 0) continue;

		// s-t �н� ã��
		// ã���� flow�� �н� ���� �ּ� �뷮
		// ã�� ���ϸ� f = 0
		int flow = fodfs(e.to, t, min(f, e.cap)); // ���� ������ �뷮�� �� ������ ���ؿ� f�� �ּҰ�����

		// s-t�н��� ã�� ���ϸ� ���� edge Ž��
		if (flow == 0) continue;

		// edge e�� �뷮 flow�� �帧 �帣���� �ϱ�
		e.cap -= flow;
		graph[e.to][e.rev].cap += flow;

		// s-t �н��� ã���� �н��� �ּ� �뷮 ��ȯ
		return flow;
	}
	// not find s-t path
	return 0;
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	graph = vector<vector<Edge>>(SIZE);

	int N{}; cin >> N; // ���� ����
	for (int n{}; n < N; ++n) {
		char a{}, b{}; int cap{};
		cin >> a >> b >> cap;
		int from = ToInt(a), to = ToInt(b);
		int fromRev = static_cast<int>(graph[from].size());
		int toRev = static_cast<int>(graph[to].size());
		// ��������� �带 �� ����.
		graph[from].emplace_back(toRev, from, to, cap); // ���� ����
		graph[to].emplace_back(fromRev, to, from, cap); // ������ ����
	}

	int s{ 0 }, t{ 25 }; // s(A) -> t(Z)���� ���� maximum flow ã��
	int maxifumFlow = 0;

	while (1) {
		// �ܿ� �׷����� s-t �н��� ������ ������ �ݺ�
		visited.assign(SIZE, 0);
		int flow = fodfs(s, t, INF);

		// s - t �н�(augmenting path)�� ã�� ���ϸ� ����
		if (flow == 0) break;

		// ����� ���� flow ��ġ��
		maxifumFlow += flow;
	}

	cout << maxifumFlow << '\n';

	return 0;
}