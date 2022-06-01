#include<iostream>
#include<vector>
#include<algorithm>

using std::cin;
using std::cout;
using std::vector;
using std::sort;
using Graph = vector<vector<int>>; // alias

int count = 1; // 이거는 함수 안이 아닌 따로 count 필요
void dfs(Graph& graph, vector<int>& chk, int now_v) {
	chk[now_v] = count++;
	for (auto& i : graph[now_v]) {
		if (chk[i] == 0) dfs(graph, chk, i);
	}
}

int main() {
	cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	int N, M, s, u, v;
	cin >> N >> M >> s;
	Graph graph(N + 1); // undirected unweighted graph V : 1~N
	vector<int> chk(N + 1, 0); // 방문 순서
	for (int i = 0; i < M; ++i) {
		cin >> u >> v;
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
	for (int i = 1; i <= N; ++i) {
		sort(graph[i].begin(), graph[i].end(), [](int a, int b) {return a > b; }); // 내림 차순
	}
	dfs(graph, chk, s);
	for (int i = 1; i <= N; ++i) {
		cout << chk[i] << "\n";
	}
	return 0;
}