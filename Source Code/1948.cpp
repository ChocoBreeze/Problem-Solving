/*
Critical Path(임계 경로)
1. 기존에 주어진 그래프로 위상정렬해서 각 정점마다 가장 늦은 시간 구하기
2. 반대로 위상 정렬 진행 -> 가장 늦은 시간에서 다음 정점의 가장 늦은 시간이 나오면 해당 간선 포함.
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
	int n, m; cin >> n >> m; // 도시 수, 도로 수
	vector<vector<Edge>> graph(n + 1), revGraph(n + 1); // 1 ~ n
	vector<int> indegree(n + 1);
	for (int i{}; i < m; ++i) {
		int a, b, c; cin >> a >> b >> c;
		graph[a].emplace_back(b, c);
		indegree[b]++;
		revGraph[b].emplace_back(a, c);
	}
	int start, finish; cin >> start >> finish;

	// 1. 첫 번째 위상 정렬 -> 각 정점까지의 최대한 늦을 수 있는 시간 구하기
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

	// 2. 두 번째 위상 정렬 -> 한 정점 최대 시간에서 다음 정점 최대 시간 나오는 경우 포함
	// 도착점까지 도달 못한 경우에는 고려하면 안 됨.
	int cnt{};
	queue<int>().swap(q); // swap with empty queue
	q.push(finish);
	vector<int> visited(n + 1, 0); // 정점 중복 방문을 막기 위해 필요함.
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