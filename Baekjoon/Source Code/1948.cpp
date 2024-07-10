/*
Critical Path(�Ӱ� ���)
1. ������ �־��� �׷����� ���������ؼ� �� �������� ���� ���� �ð� ���ϱ�
2. �ݴ�� ���� ���� ���� -> ���� ���� �ð����� ���� ������ ���� ���� �ð��� ������ �ش� ���� ����.
*/
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Edge {
	int to, weight;
	Edge(int to, int weight) : to(to), weight(weight) {}
};

int main() {
	cin.tie(nullptr), ios::sync_with_stdio(false);
	int n, m; cin >> n >> m; // ���� ��, ���� ��
	vector<vector<Edge>> graph(n + 1), revGraph(n + 1); // 1 ~ n
	vector<int> indegree(n + 1);
	for (int i{}; i < m; ++i) {
		int a, b, c; cin >> a >> b >> c;
		graph[a].emplace_back(b, c);
		indegree[b]++;
		revGraph[b].emplace_back(a, c);
	}
	int start, finish; cin >> start >> finish;

	// 1. ù ��° ���� ���� -> �� ���������� �ִ��� ���� �� �ִ� �ð� ���ϱ�
	queue<int> q;
	q.push(start);
	vector<int> maxDist(n + 1, -1);
	maxDist[start] = 0;
	while (!q.empty()) {
		int now = q.front(); q.pop();
		for (auto& e : graph[now]) { // to, weight
			maxDist[e.to] = max(maxDist[e.to], maxDist[now] + e.weight);
			indegree[e.to]--;
			if (indegree[e.to] == 0) {
				q.push(e.to);
			}
		}
	}

	// 2. �� ��° ���� ���� -> �� ���� �ִ� �ð����� ���� ���� �ִ� �ð� ������ ��� ����
	// ���������� ���� ���� ��쿡�� ����ϸ� �� ��.
	int cnt{};
	queue<int>().swap(q); // swap with empty queue
	q.push(finish);
	vector<int> visited(n + 1, 0); // ���� �ߺ� �湮�� ���� ���� �ʿ���.
	while (!q.empty()) {
		int now{ q.front() }; q.pop();
		for (auto& e : revGraph[now]) { // to, weight

			if (maxDist[now] == maxDist[e.to] + e.weight) {
				cnt++;
				// cout << e.to << ' ' << now << '\n';
				if (visited[e.to] == 0) {
					q.push(e.to);
					visited[e.to] = 1;
				}
			}
		}
	}

	cout << maxDist[finish] << '\n' << cnt << '\n';

	return 0;
}