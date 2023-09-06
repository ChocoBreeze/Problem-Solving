/*
한 간선의 용량이 1줄면 최대 유량도 1이 줄어드는 경우 그 간선을 완전 중요한 간선이라고 부른다.
1. 최대 유량 흘리기
2. 포화 간선 중에서 완전 중요한 간선 찾기 (용량이 1줄었을 때 최대 용량이 1 줄어야 함)

최대한 흘린 상태에서 -> 간선(u,v)마다 flow 흘릴 수 있는지(u -> v) 확인하기.
Ford-Fulkerson
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

constinit const int INF = 1 << 30;

struct Edge {
	int rev, from, to, cap, ori; // 역방향 간선의 인덱스, 시작, 도착, 용량, 원래 간선인지 여부
	Edge(int rev, int from, int to, int cap, int ori) : rev(rev), from(from), to(to), cap(cap), ori(ori) {}
};

vector<vector<Edge>> graph;
vector<Edge> edges;
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
	int T; cin >> T;
	while (T--) {
		int N, M; cin >> N >> M; // 정점 수, 간선 수
		graph = vector<vector<Edge>>(N + 1); // 1(src) ~ N(sink)
		for (int m{}; m < M; ++m) {
			int f, t, b; cin >> f >> t >> b; // f -> t (cap = b)
			int fromRev = static_cast<int>(graph[f].size());
			int toRev = static_cast<int>(graph[t].size());
			graph[f].emplace_back(toRev, f, t, b, 1);
			graph[t].emplace_back(fromRev, t, f, 0, 0);
		}

		// 1. 최대 유량 구하기
		int maxFlow{}, src{ 1 }, sink{ N };
		while (1) {
			visited = vector<int>(N + 1, 0);
			int flow = fodfs(src, sink, INF);
			if (flow == 0) break;
			maxFlow += flow;
		}

		// 2. 포화 간선 중에서 완전 중요한 간선 찾기 (용량이 1줄었을 때 최대 용량이 1 줄어야 함)
		// 기존 코드에서 가상의 간선도 고려하는 문제가 있었음.
		int answer{};
		for (vector<Edge>& row : graph) {
			for (Edge& e : row) {
				if (e.cap) continue; // 포화 간선만
				if (!e.ori) continue; // 가상 간선은 빼고
				int s{ e.from }, t{ e.to }; // s -> t 갈 수 있는지 확인
				queue<int> q;
				q.push(s);
				vector<int> visited(N + 1, -1);
				while (!q.empty() && visited[t] == -1) {
					int now = q.front(); q.pop();
					for (Edge& e : graph[now]) {
						if (e.cap > 0 && visited[e.to] == -1) {
							q.push(e.to);
							visited[e.to] = now;
							if (e.to == t) break;
						}
					}
				}
				if (visited[e.to] == -1) ++answer; // 해당 간선의 용량이 하나 줄면 최대 용량도 1 줄어 듦
			}
		}
		cout << answer << '\n';
	}
	return 0;
}