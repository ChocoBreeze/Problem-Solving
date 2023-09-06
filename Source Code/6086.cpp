// Network Flow
// 공부
// Ford-Fulkerson
// 문제 해결력을 높이는 알고리즘과 자료구조 책 참고.

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
	// rev : (to, from)이 graph[to]에서 몇 번째 요소인지
	// cap : capacity
	int rev, from, to, cap;
	Edge(int rev, int from, int to, int cap) : rev(rev), from(from), to(to), cap(cap) {}
};

vector<vector<Edge>> graph; // adjacency list

// 잔여 그래프 위에 s-t패스를 찾기(dfs)
// 반환값은 s-t패스에서 용량의 최솟값(찾지 못한 경우 0)
// f: s에서 v로 도착하는 과정의 각 변 용량의 최솟값
vector<int> visited;
int fodfs(int v, int t, int f) { // 포드포커슨이라서 fodfs인 듯?
	// 끝점 t에 도달시 반환
	if (v == t) return f;

	// DFS
	visited[v] = true;
	for (Edge& e : graph[v]) {
		if (visited[e.to]) continue;

		// 용량 0인 edge는 실제로 존재하지 않음. (가상의 간선)
		if (e.cap == 0) continue;

		// s-t 패스 찾기
		// 찾으면 flow는 패스 위의 최소 용량
		// 찾지 못하면 f = 0
		int flow = fodfs(e.to, t, min(f, e.cap)); // 현재 간선의 용량과 이 때까지 구해온 f중 최소값으로

		// s-t패스를 찾지 못하면 다음 edge 탐색
		if (flow == 0) continue;

		// edge e에 용량 flow인 흐름 흐르도록 하기
		e.cap -= flow;
		graph[e.to][e.rev].cap += flow;

		// s-t 패스를 찾으면 패스의 최소 용량 반환
		return flow;
	}
	// not find s-t path
	return 0;
}

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
	int maxifumFlow = 0;

	while (1) {
		// 잔여 그래프에 s-t 패스가 없어질 때까지 반복
		visited.assign(SIZE, 0);
		int flow = fodfs(s, t, INF);

		// s - t 패스(augmenting path)를 찾지 못하면 종료
		if (flow == 0) break;

		// 계산해 나온 flow 합치기
		maxifumFlow += flow;
	}

	cout << maxifumFlow << '\n';

	return 0;
}