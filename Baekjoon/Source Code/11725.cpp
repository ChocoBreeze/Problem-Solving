#include<iostream>
#include<vector>
#include<utility> // pair

using std::cout;
using std::cin;
using std::pair;
using std::make_pair;
using std::vector;

using Graph = vector<vector<int>>;

void dfs(Graph& graph, vector<int>& root, int now) {
	for (auto& i : graph[now]) {
		if (root[i] == -1) {
			root[i] = now;
			dfs(graph, root, i);
		}
	}
}

int main() {
	cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	int N, a, b;
	cin >> N;
	Graph graph(N + 1);
	for (int i = 1; i < N; ++i) {
		cin >> a >> b;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}
	vector<int> root(N + 1, -1);
	root[1] = 0;
	dfs(graph,root,1);
	for (int i = 2; i <= N; ++i) {
		cout << root[i] << "\n";
	}
	return 0;
}