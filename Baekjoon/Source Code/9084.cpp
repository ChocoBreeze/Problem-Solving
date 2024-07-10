#include<iostream>
#include<vector>

using std::cin;
using std::cout;
using std::vector;

int main() {
	cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	int T, N, M;
	cin >> T;
	for (int t = 0; t < T; ++t) {
		cin >> N; // 동전 수
		vector<int> coins(N,0);
		for (auto& i : coins) {
			cin >> i;
		}
		cin >> M; // 만들어야 할 금액
		vector<vector<int>> DP(N + 1, vector<int>(M + 1, 0));
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j <= M; ++j) {
				DP[i + 1][j] = DP[i][j];
				if (j == coins[i]) DP[i + 1][j]++;
				if (j > coins[i]) {
					DP[i + 1][j] += DP[i + 1][j - coins[i]];
				}
			}
		}
		cout << DP[N][M]<<"\n";
	}
	return 0;
}