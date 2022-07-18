// 간선의 가중치가 > 0
// 출발 도시가 주어진다
// Dijkstra!!- min heap
#include <iostream>
#include <queue>

using namespace std;

const int INF = 2000000000;

struct e_t {
	int to;
	int weight;
	bool operator<(const e_t& others) const {
		return this->weight > others.weight;
	}
	e_t(int t, int w) : to(t), weight(w) {}
};

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	int N, M;
	cin >> N >> M;
	int a, b, c;
	vector<vector<e_t>> Edges(N + 1);
	for (int i = 0; i < M; ++i) {
		cin >> a >> b >> c;
		Edges[a].push_back(e_t(b, c));
	}
	cin >> a >> b;
	vector<int> visited(N + 1, INF);
	visited[a] = 0;
	priority_queue<e_t> PQ;
	PQ.push(e_t(a, 0));
	while (!PQ.empty()) {
		e_t now = PQ.top();
		PQ.pop();
		if (now.weight > visited[now.to]) continue;
		for (auto& next : Edges[now.to]) {
			if (visited[next.to] > visited[now.to] + next.weight) {
				visited[next.to] = visited[now.to] + next.weight;
				PQ.push(e_t(next.to, visited[now.to] + next.weight));
			}
		}
	}
	cout << visited[b];
	return 0;
}