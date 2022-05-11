// 1 ~ N 까지 최단 거리
// but 2, 3정점을 거쳐야 함.
// 1초당 처리 가능한 연산 수 = 10^9
// floyd-warshall --> N^3 --> 512,000,000 (상한 값)
// 충분히 1초에 처리 가능하다 생각했음.
#include<iostream>
#include<vector>
#include<climits>
#include<algorithm> // min

using std::cin;
using std::cout;
using std::vector;
using std::min;
using Graph = vector<vector<int>>;

const int INF = 200000001; // 200000 * 1000 = 200000000


int main() {
	cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	int N, E; // 정점 수, 간선 수
	int a, b, c, v1, v2;
	cin >> N >> E;
	// undirected weighted graph
	Graph dp(N + 1, vector<int>(N + 1, INF)); // 1 ~ N
	for (int i = 0; i < E; ++i) {
		cin >> a >> b >> c;
		dp[a][b] = c;
		dp[b][a] = c;
	}
	for (int i = 1; i <= N; ++i) {
		dp[i][i] = 0; // i -> i
	}
	// dp 전이
	for (int k = 1; k <= N; ++k) {
		for (int i = 1; i <= N; ++i) {
			for (int j = 1; j <= N; ++j) {
				dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);
			}
		}
	}
	// c >= 1이므로 negative cycle 고려 필요 없음.
	cin >> v1 >> v2;
	if (dp[1][v1] >= INF || dp[v1][v2] >= INF || dp[v2][N] >= INF) {
		if (dp[1][v2] >= INF || dp[v2][v1] >= INF || dp[v1][N] >= INF) {
			cout << -1;
		}
		else cout << dp[1][v2] + dp[v2][v1] + dp[v1][N];
	}
	else if (dp[1][v2] >= INF || dp[v2][v1] >= INF || dp[v1][N] >= INF) {
		cout << dp[1][v1] + dp[v1][v2] + dp[v2][N];
	}
	else cout << min(dp[1][v1] + dp[v1][v2] + dp[v2][N], dp[1][v2] + dp[v2][v1] + dp[v1][N]);
	return 0;
}