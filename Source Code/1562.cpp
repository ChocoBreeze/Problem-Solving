// bit field dp
#include <iostream>
#include <vector>

using namespace std;

const int SIZE = 1 << 10; // 1024

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	int N; // 길이
	cin >> N;
	vector<vector<vector<int>>> dp(N + 1, vector<vector<int>>(SIZE, vector<int>(10, 0)));
	// 길이 - bitfield - 1 ~ 9
	// 길이 = 1
	for (int i = 1; i <= 9; ++i) {
		int bit = 1 << i;
		dp[1][bit][i] = 1;
	}
	for (int l = 2; l <= N; ++l) { // length
		for (int b = 1; b < SIZE; ++b) { // bitfield
			for (int n = 0; n <= 9; ++n) { // 마지막 숫자
				if (dp[l - 1][b][n] == 0) continue;
				if (n >= 1) {
					int bit_d = 1 << (n - 1);
					dp[l][b | bit_d][n - 1] += dp[l - 1][b][n];
					dp[l][b | bit_d][n - 1] %= 1000000000;
				}
				if (n <= 8) {
					int bit_u = 1 << (n + 1);
					dp[l][b | bit_u][n + 1] += dp[l - 1][b][n];
					dp[l][b | bit_u][n + 1] %= 1000000000;
				}
			}
		}
	}
	int sum = 0;
	for (int n = 0; n <= 9; n++) {
		sum += dp[N][SIZE - 1][n];
		sum %= 1000000000;
	}
	cout << sum;
	return 0;
}