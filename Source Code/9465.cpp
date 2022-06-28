/*
dp[1][i] = dp[0][i-1], dp[0][i-2], dp[1][i-2]
dp[0][i] = dp[1][i-1], dp[0][i-2], dp[1][i-2]
*/
#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;
int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	int T, n;
	cin >> T;
	for (int t = 0; t < T; ++t) {
		cin >> n;
		vector<vector<int>> s(2, vector<int>(n, 0));
		vector<vector<int>> dp(2, vector<int>(n, 0));
		for (int i = 0; i < 2; ++i) {
			for (auto& i : s[i]) {
				cin >> i;
			}
		}
		dp[0][0] = s[0][0];
		dp[1][0] = s[1][0];
		
		for (int i = 1; i < n; ++i) {
			if (i == 1) {
				dp[0][i] = dp[1][i - 1] + s[0][i];
				dp[1][i] = dp[0][i - 1] + s[1][i];
			}
			else {
				int max_0, max_1;
				max_0 = max(dp[1][i - 1], max(dp[0][i - 2], dp[1][i - 2]));
				max_1 = max(dp[0][i - 1], max(dp[0][i - 2], dp[1][i - 2]));
				dp[0][i] = max_0 + s[0][i];
				dp[1][i] = max_1 + s[1][i];
			}
		}
		int answer1, answer2;
		answer1 = max(dp[0][n - 1], dp[1][n - 1]);
		answer2 = max(dp[0][n - 2], dp[1][n - 2]);
		cout << max(answer1, answer2) << "\n";
	}
	return 0;
}