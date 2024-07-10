// floyd - warshall
#include<iostream>
#include<vector>
#include<climits> // INT_MAX
#include<algorithm> // min

using std::cin;
using std::cout;
using std::vector;
using std::min;
using Graph = vector<vector<long long>>;

int main() {
	int n, m;
	int a, b, c;
	cin >> n >> m;
	Graph graph(n+1,vector<long long>(n+1, INT_MAX)); // 1~n
	for (int i = 0; i < m; ++i) {
		cin >> a >> b >> c;
		graph[a][b] = graph[a][b] < c ? graph[a][b] : c;
	}
	for (int i = 1; i <= n; ++i) { 
		graph[i][i] = 0;
	}
	// floyd - warshall
	// i - 1번에서 i번째 까지 정점을 이용함
	// j -> k를 가는 경로와 j -> i -> k로 가는 경로를 비교
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			for (int k = 1; k <= n; ++k) {
				graph[j][k] = min(graph[j][k], graph[j][i] + graph[i][k]);
			}
		}
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			if (graph[i][j] == INT_MAX) cout << "0 ";
			else cout << graph[i][j] << " ";
		}
		cout << "\n";
	}
	return 0;
}