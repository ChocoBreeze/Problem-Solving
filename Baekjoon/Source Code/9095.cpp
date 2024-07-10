/*
0 1 1 1 1 1 1 1 1 1 1
0 1 2 3 5 ..
0 1 2 4 7 ..
i = 1 dp[i][j] = dp[i][j-1]
i = 2 dp[i][j] = dp[i][j-1] + dp[i][j-2]
i = 3 dp[i][j] = dp[i][j-1] + dp[i][j-2] + dp[i][j-3]
*/
#include<iostream>
#include<vector>

using std::cin;
using std::cout;
using std::vector;

int main() {
	cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	int T, n; // 1~10
	vector<int> w = { 1,2,3 };
	vector<vector<int>> dp (4, vector<int>(11, 0));
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j <= 10; ++j) {
			if (j < w[i]) dp[i + 1][j] = dp[i][j];
			else if (j == w[i]) dp[i + 1][j] = dp[i][j] + 1;
			else {
				if (i == 0) dp[i + 1][j] = dp[i + 1][j - 1];
				else if (i == 1) dp[i + 1][j] = dp[i + 1][j - 1] + dp[i + 1][j - 2];
				else dp[i + 1][j] = dp[i + 1][j - 1] + dp[i + 1][j - 2] + dp[i+1][j-3];
			}
		}
	}
	cin >> T;
	for(int i=0;i<T;++i) {
		cin >> n;
		cout << dp[3][n] << "\n";
	}
	return 0;
}