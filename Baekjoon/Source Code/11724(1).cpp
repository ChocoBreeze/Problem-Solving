// connected component
#include<iostream>
#include<queue> // bfs
#include<vector>

using std::cout;
using std::cin;
using std::queue;
using std::vector;

using Graph = vector<vector<int>>;

void bfs(Graph& graph, vector<int>& chk, int count, int start) {
	vector<bool> visited(size(graph) + 1, false);
	queue<int> Q;
	Q.push(start);
	chk[start] = count;
	visited[start] = true;
	while (!Q.empty()) {
		auto i = Q.front();
		Q.pop();
		for (auto& j : graph[i]) {
			if (!visited[j]) {
				visited[j] = true;
				Q.push(j);
				chk[j] = count;
			}
		}
	}
}

int main() {
	cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	int N, M, u, v;
	cin >> N >> M;
	Graph graph(N + 1); // 1~N
	for (int i = 0; i < M; ++i) {
		cin >> u >> v;
		// undirected
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
	int count = 0;
	vector<int> chk(N + 1, -1);
	for (int i = 1; i <= N; ++i) {
		if (chk[i] != -1) continue; // 이미 탐색 완료
		bfs(graph, chk, count, i);
		count++;
	}
	cout << count;
	return 0;
}