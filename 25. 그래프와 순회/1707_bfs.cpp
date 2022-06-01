#include<iostream>
#include<vector> 
#include<queue>

using std::cout;
using std::cin;
using std::vector;
using std::queue;

bool bfs(vector<vector<int>>& Edge, vector<int>& coloring, int cur_v) {
	queue<int> Q;
	int cur_color = 0;
	coloring[cur_v] = cur_color;
	Q.push(cur_v);
	while (!Q.empty()) {
		int now = Q.front();
		Q.pop();
		for (auto& adj_v : Edge[now]) {
			if (coloring[adj_v] != -1) { // color already setting
				if (coloring[adj_v] == coloring[now]) return false; // 같은 색
				continue;
			}
			coloring[adj_v] = 1 - coloring[now];
			Q.push(adj_v);
		}
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
		vector<vector<int>> Edge(V + 1);// 1~V
		int chk = 0;
		for (int j = 0; j < E; ++j) {
			cin >> u >> v;
			Edge[u].push_back(v);
			Edge[v].push_back(u);
		}
		bool is_bipartite = true;
		for (int j = 1; j <= V; ++j) {
			if (coloring[j] != -1) continue; // 이미 색 정해짐
			if (!bfs(Edge, coloring, j)) is_bipartite = false;
		}
		if (is_bipartite) cout << "YES\n";
		else cout << "NO\n";
	}
	return 0;
}