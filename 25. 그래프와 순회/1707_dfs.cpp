#include<iostream>
#include<vector> 

using std::cout;
using std::cin;
using std::vector;

bool dfs(const vector<vector<int>>& Edge, vector<int>& coloring, int v, int cur = 0) {
	coloring[v] = cur;
	for (auto adj_v : Edge[v]) {
		if (coloring[adj_v] != -1) { // 색이 이미 정해짐
			if (coloring[adj_v] == cur) return false; // same color
			continue; // 다른색인 경우 --> 탐색하지 x
		}
		// 인접 vertex 색을 바꾸고 dfs로 탐색
		if (!dfs(Edge, coloring, adj_v, 1 - cur)) return false;
	}
	return true;
}

int main() {
	cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	int K, V, E, u, v;
	cin >> K;
	for (int i = 0; i < K; ++i) {
		cin >> V >> E;
		vector<int> coloring(V + 1, -1); // 1~V
		vector<vector<int>> Edge(V + 1); // 1~V
		for (int j = 0; j < E; ++j) {
			cin >> u >> v;
			Edge[u].push_back(v);
			Edge[v].push_back(u);
		}
		bool is_bipartite = true;
		for (int j = 1; j <= V; ++j) {
			if(coloring[j] != -1) continue; // 이미 탐색 완료
			if (!dfs(Edge, coloring, j)) is_bipartite = false;
		}
		if (is_bipartite) cout << "YES\n";
		else cout << "NO\n";
	}
	return 0;
}