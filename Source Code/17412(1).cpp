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
	P개의 단방향 길로 연결
	1 -> 2번으로 가는 서로 다른 경로 찾기
	이때 한 경로에 포함된 길이 다른 경로에 포함되면 안된다. => cap = 1
	*/
	const int SIZE = N + 1;
	graph = vector<vector<Edge>>(SIZE); // 1 ~ N
	for (int p{}; p < P; ++p) {
		int from, to; cin >> from >> to;
		int fromRev = static_cast<int>(graph[from].size());
		int toRev = static_cast<int>(graph[to].size());
		graph[from].emplace_back(toRev, from, to, 1); // 진짜 간선
		graph[to].emplace_back(fromRev, to, from, 0); // 가짜 간선
	}

	int s{ 1 }, e{ 2 }, maxFlow{};

	while (1) {
		visited.assign(SIZE, -1); // 방문확인 및 어디에서 왔는지 저장
		vector<pair<int, int>> path(SIZE); // 경로상의 간선들을 저장해두어 나중에 참조
		// path[i] : Edge e의 to가 i인 간선의 {from, index} 저장
		// index(path[i].second) : from -> i(to)의 간선이 from의 몇 번째 index인지.

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
					if (edg.to == e) break; // 도달
				}
				++index;
			}
		}
		if (visited[e] == -1) break;
		
		int flow = INF;
		for (int i{ e }; i != s; i = visited[i]) { // 최소 flow 갱신
			Edge& e = graph[path[i].first][path[i].second];
			flow = min(flow, e.cap);
		}
		for (int i{ e }; i != s; i = visited[i]) { // flow 흘리기
			Edge& e = graph[path[i].first][path[i].second];
			e.cap -= flow;
			graph[e.to][e.rev].cap += flow;
		}
		maxFlow += flow;
	}
	cout << maxFlow << '\n';

	return 0;
}