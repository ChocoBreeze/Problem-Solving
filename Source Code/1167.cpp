// https://blog.myungwoo.kr/112
// 1. 임의의 점(A)에서 가장 먼 점(B)
// 2. B에서 가장 먼 점인 C --> 트리의 지름 = B~C 사이의 거리
// 모든 정점에 대해 dfs - 시간 초과
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
	for (auto i : graph[now]) {
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
	int V;
	cin >> V;
	int n, to, weight;
	vector<vector<Edge>> graph(V + 1); // 1~V
	for (int i = 0; i < V; ++i) {
		cin >> n;
		while (1) {
			cin >> to;
			if (to == -1) break;
			cin >> weight;
			graph[n].push_back(Edge(to, weight));
		}
	}
	// 1. 1번 정점에서 가장 먼 점 찾기
	int far = 0, i = 1;
	vector<bool> chk(V + 1, false);
	chk[1] = true;
	dfs(graph, chk, far, i, 0);

	// 2. far에서 가장 먼 점까지의 거리 = 트리의 지름.
	chk.assign(V + 1, false);
	chk[far] = true;
	i = far;
	far = 0;
	dfs(graph, chk, far, i, 0);
	cout << answer;
	return 0;
}