// 반례 https://www.acmicpc.net/board/view/58934
// 접근법을 생각해보기.

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct e_t {
	int to;
	int weight;
	e_t(int t, int w) : to(t), weight(w) {}
	bool operator< (const e_t& other) const {
		return this->weight > other.weight; // 내림차순 - min heap
	}
};

struct edge {
	int from;
	int to;
	edge(int f, int t) : from(f), to(t) {}
};

const int INF = 1000000000;
int N, M, S, D;

int dijkstra(vector<vector<e_t>>& edges) {
	vector<int> dist(N, INF);
	vector<vector<int>> dist_from(N);
	priority_queue<e_t> PQ;
	PQ.push(e_t(S, 0));
	dist[S] = 0;
	while (!PQ.empty()) {
		e_t now = PQ.top();
		PQ.pop();
		if (now.weight > dist[now.to]) continue;
		for (auto& n : edges[now.to]) {
			if (dist[n.to] > dist[now.to] + n.weight) {
				dist[n.to] = dist[now.to] + n.weight;
				dist_from[n.to].clear();
				dist_from[n.to].push_back(now.to);
				PQ.push(e_t(n.to, dist[n.to]));
			}
			else if(dist[n.to] == dist[now.to] + n.weight) {
				dist_from[n.to].push_back(now.to);
			}
		}
	}
	queue<edge> Q;
	for (auto& i : dist_from[D]) {
		Q.push(edge(i, D)); // from, to
	}
	while (!Q.empty()) {
		edge now = Q.front();
		Q.pop();
		for (auto& n : edges[now.from]) { 
			if (n.to == now.to) {
				n.weight = INF; // from -> to 가는 간선 제거
				for (auto& i : dist_from[now.from]) { // now.from까지 갈 수 있는 정점들 넣기
					Q.push(edge(i, now.from));
				}
				dist_from[now.from].clear();
				break;
			}
		}
	}
	return dist[D];
}

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);

	while (1) {
		cin >> N >> M;
		if (N == 0 && M == 0) break;
		cin >> S >> D; // 출발, 도착
		int u, v, p;
		vector<vector<e_t>> edges(N);
		for (int m = 0; m < M; ++m) {
			cin >> u >> v >> p;
			edges[u].push_back(e_t(v, p));
		}
		int first_d = dijkstra(edges);
		while (1) {
			int second_d = dijkstra(edges);
			if (second_d == INF) {
				cout << "-1\n";
				break;
			}
			if (second_d > first_d) {
				cout << second_d << "\n";
				break;
			}
		}
	}
	return 0;
}