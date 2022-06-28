// Floyd - Warshall
#include<iostream>
#include<vector>
#include<climits> // INT_MAX
#include<algorithm>

using std::cout;
using std::cin;
using std::vector;
using std::min;
using Graph = vector<vector<long long>>;

int main() {
	cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	int V, E, a, b, c;
	cin >> V >> E;
	Graph graph(V + 1, vector<long long>(V + 1, INT_MAX));
	for (int i = 1; i <= V; ++i) {
		graph[i][i] = 0;
	}
	for (int i = 1; i <= E; ++i) {
		cin >> a >> b >> c;
		graph[a][b] = c;
	}
	for (int i = 1; i <= V; ++i) {
		for (int j = 1; j <= V; ++j) {
			for (int k = 1; k <= V; ++k) {
				if (graph[j][k] > graph[j][i] + graph[i][k]) {
					graph[j][k] = graph[j][i] + graph[i][k];
				}
			}
		}
	}
	// cycle 여부 판정?
	// 그냥 모든 경우 다 확인.
	long long answer = -1;
	for (int i = 1; i <= V; ++i) {
		for (int j = i + 1; j <= V; ++j) {
			if (graph[i][j] != INT_MAX && graph[j][i] != INT_MAX)
				answer = answer == -1 ? graph[i][j] + graph[j][i] : min(answer, graph[i][j] + graph[j][i]);
		}
	}
	cout << answer;
	return 0;
}