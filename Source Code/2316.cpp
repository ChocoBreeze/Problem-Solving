// https://www.acmicpc.net/problem/17412 +
// 이때 한 번 방문했던 도시(1, 2번 도시 제외)를 두 번 이상 방문하지 않으려 한다.

// 같은 도시를 두 번 방문하지 않기 위해서 기존에 1개였던 정점을 2개로 나누어
// 2개로 나뉜 정점 사이에 용량을 1로 설정하기!
// 기존에 4정점을 4a와 4b으로 나누어서. 4a -> 4b을 연결
// 4a에는 들어오는 간선, 4b에는 나가는 간선만을 연결

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
	cin >> N >> P; // N개의 도시가 P개의 양방향 길로 연결되어 있다.

	const int SIZE = (N << 1) + 1; // 1 << N이 아님..
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
		cin >> f >> t; // a - b (양방향 길)
		// 1 -> 1, 2
		// 2 -> 3, 4
		int fa{ 2 * f - 1 }, fb{ 2 * f }, ta{ 2 * t - 1 }, tb{ 2 * t };
		// fb -> ta
		int taRev = static_cast<int>(graph[ta].size());
		int fbRev = static_cast<int>(graph[fb].size());
		graph[fb].emplace_back(taRev, fb, ta, 100); // cap 상관 없음
		graph[ta].emplace_back(fbRev, ta, fb, 0); // 실제 존재하지 않는 역방향 간선

		// tb -> fa
		int faRev = static_cast<int>(graph[fa].size());
		int tbRev = static_cast<int>(graph[tb].size());
		graph[tb].emplace_back(faRev, tb, fa, 100); // cap 상관 없음
		graph[fa].emplace_back(tbRev, fa, tb, 0); // 실제 존재하지 않는 역방향 간선
	}

	int maxFlow{}, src{ 2 }, sink{ 3 };
	// src 1 -> 2 (1이 나갈 수 있는 정점 = 2)
	// sink 2 -> 3 (2로 들어올 수 있는 정점 = 3)
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
					if (edg.to == sink) break; // 도달
				}
				++index;
			}
		}

		if (visited[sink] == -1) break;

		int flow = INF;
		for (int i{ sink }; i != src; i = visited[i]) { // 최소 flow 갱신
			Edge& e = graph[path[i].first][path[i].second];
			flow = min(flow, e.cap);
		}
		for (int i{ sink }; i != src; i = visited[i]) { // flow 흘리기
			Edge& e = graph[path[i].first][path[i].second];
			e.cap -= flow;
			graph[e.to][e.rev].cap += flow;
		}
		maxFlow += flow;
	}

	cout << maxFlow << '\n';


	return 0;
}