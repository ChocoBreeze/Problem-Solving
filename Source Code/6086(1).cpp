// Network Flow
// 공부
// Ford-Fulkerson alg -> O((V+E)f) : f라는 값 때문에 최악의 경우에는 낭비 발생!
// Edmonds-Karp alg -> O(VE^2) : DFS 대신 BFS를 통해 그때 그때의 가장 짧은 경로 찾기
// https://m.blog.naver.com/kks227/220804885235 참고

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

constinit const int INF = 1 << 30;
constinit const int SIZE = 52; // 0 ~ 51

// ABCD...Zabcd...z
inline int ToInt(char c) {
	if (c & ' ') return c - 'a' + 26;
	else return c - 'A';
}

struct Edge {
	// rev : (to, from)이 graph[to]에서 몇 번째 요소인지
	// cap : capacity
	int rev, from, to, cap;
	Edge(int rev, int from, int to, int cap) : rev(rev), from(from), to(to), cap(cap) {}
};

vector<vector<Edge>> graph; // adjacency list
vector<int> prevVisited;

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	graph = vector<vector<Edge>>(SIZE);

	int N{}; cin >> N; // 간선 개수
	for (int n{}; n < N; ++n) {
		char a{}, b{}; int cap{};
		cin >> a >> b >> cap;
		int from = ToInt(a), to = ToInt(b);
		int fromRev = static_cast<int>(graph[from].size());
		int toRev = static_cast<int>(graph[to].size());
		// 양방향으로 흐를 수 있음.
		graph[from].emplace_back(toRev, from, to, cap); // 실제 간선
		graph[to].emplace_back(fromRev, to, from, cap); // 가상의 간선
	}

	int s{ 0 }, t{ 25 }; // s(A) -> t(Z)까지 가는 maximum flow 찾기
	int maximumFlow{};

	while (1) {
		prevVisited.assign(SIZE, -1); // 방문확인 및 어디에서 왔는지 저장
		vector<pair<int,int>> path(SIZE);// 경로상의 간선들을 저장해두어 나중에 참조
		// path[i] : Edge e의 to가 i인 간선의 {from, index} 저장
		// index : from -> i의 간선이 from의 몇 번째 index인지.
		queue<int> Q;
		Q.push(s);

		while (!Q.empty() && prevVisited[t] == -1) {
			int now = Q.front(); Q.pop();
			int index{};
			for (Edge& e : graph[now]) {
				if (e.cap > 0 && prevVisited[e.to] == -1) {
					Q.push(e.to);
					prevVisited[e.to] = now;
					path[e.to] = make_pair(now, index);
					if (e.to == t) break;
				}
				++index;
			}
		}
		if (prevVisited[t] == -1) break; // 더 이상 augmenting path 존재 X

		int flow = INF;
		for (int i = t; i != s; i = prevVisited[i]) { // find maxflow
			Edge& e = graph[path[i].first][path[i].second];
			flow = min(flow, e.cap);
		}
		for (int i = t; i != s; i = prevVisited[i]) {
			Edge& e = graph[path[i].first][path[i].second];
			e.cap -= flow;
			graph[e.to][e.rev].cap += flow;
		}
		maximumFlow += flow;
	}

	cout << maximumFlow << '\n';

	return 0;
}