// https://blog.myungwoo.kr/112
// 1. 임의의 점(A)에서 가장 먼 점(B)
// 2. B에서 가장 먼 점인 C --> 트리의 지름 = B~C 사이의 거리
#include<iostream>
#include<vector>

using std::cin;
using std::cout;
using std::vector;

struct Edge {
	int to;
	int weight;
	Edge(int to, int weight) : to(to), weight(weight) {}
};

int answer = -1;
void dfs(vector<vector<Edge>>& graph,vector<bool>&chk, int& far, int now, int count) {
	for (auto& i : graph[now]) {
		if (!chk[i.to]) {
			chk[i.to] = true;
			dfs(graph, chk, far, i.to, count + i.weight);
			chk[i.to] = false;
		}
	}
	if (answer < count) {
		answer = count;
		far = now;
	}
}

int main() {
	cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	int n;
	cin >> n;
	int par, chi, weight;
	vector<vector<Edge>> graph(n + 1); // 1 ~ n
	for (int i = 1; i < n; ++i) {
		cin >> par >> chi >> weight;
		graph[par].push_back(Edge(chi, weight));
		graph[chi].push_back(Edge(par, weight));
	}
	// 1. 1번 정점에서 가장 먼 점 찾기
	int far = 0, i = 1;
	vector<bool> chk(n + 1, false);
	chk[1] = true;
	dfs(graph, chk, far, i, 0);

	// 2. far에서 가장 먼 점까지의 거리 = 트리의 지름.
	chk.assign(n + 1, false);
	chk[far] = true;
	i = far;
	far = 0;
	dfs(graph, chk, far, i, 0);
	cout << answer;
	return 0;
}