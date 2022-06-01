#include<iostream>
#include<vector>
#include<queue>
#include<algorithm> // sort

using std::cin;
using std::cout;
using std::vector;
using std::sort;
using std::queue;
using Graph = vector<vector<int>>; // alias

void bfs(Graph& graph, vector<int>& chk, int start) {
	int count = 1;
	chk[start] = count++;
	std::queue<int> Q;
	Q.push(start);
	while (!Q.empty()) {
		int now = Q.front();
		Q.pop();
		for (auto& i : graph[now]) {
			if (chk[i] == 0) {
				chk[i] = count++;
				Q.push(i);
			}
		}
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
		sort(graph[i].begin(), graph[i].end(), [](int a, int b) {return a > b; });
	}
	bfs(graph, chk, s);
	for (int i = 1; i <= N; ++i) {
		cout << chk[i] << "\n";
	}
	return 0;
}