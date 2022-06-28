#include <iostream>
#include <queue> // max_heap
#include <vector>
#include <utility> // pair

using namespace std;

const int INF = 100000000;

struct Edge {
	int s;
	int cost;
	Edge(int s, int cost) : s(s), cost(cost) {}
};

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);

	int n, m;
	cin >> n; // 도시
	cin >> m; // 버스

	int a, b, c;
	vector<vector<Edge>> graph(n + 1); // 1 ~ n
	for (int i = 0; i < m; ++i) {
		cin >> a >> b >> c;
		graph[a].push_back(Edge(b, c));
	}
	cin >> a >> b; // a -> b까지 최단 경로

	vector<int> dist(n + 1, INF);
	vector<int> dist_record(n + 1, -1);
	dist[a] = 0;
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> Q;
	Q.push(make_pair(dist[a], a));

	while (!Q.empty()) {
		auto& now = Q.top();
		int v = now.second; // 정점
		int d = now.first; // 거리
		Q.pop();

		if (d > dist[v]) continue; // 갱신할 필요 없음

		for (auto& e : graph[v]) {
			if (dist[e.s] > dist[v] + e.cost) {
				dist[e.s] = dist[v] + e.cost;
				dist_record[e.s] = v;
				Q.push(make_pair(dist[e.s], e.s));
			}
		}
	}
	vector<int> answer;
	int make_answer = b;
	answer.push_back(b);
	while (make_answer != a) {
		answer.push_back(dist_record[make_answer]);
		make_answer = dist_record[make_answer];
	}

	cout << dist[b] << "\n"; // 최소 비용
	cout << answer.size() << "\n"; // 포함된 도시 수
	for (auto i = rbegin(answer); i != rend(answer); ++i) { // 경로
		cout << *i << " ";
	}

	return 0;
}