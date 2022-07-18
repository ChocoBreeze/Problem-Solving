#include<iostream>
#include<vector>
#include<algorithm>
#include<string>

using namespace std;
int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	int n, m, temp, answer = 0;
	cin >> n >> m;
	vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
	vector<vector<int>> input(n + 1, vector<int>(m + 1, 0));
	string str;
	for (int i = 1; i <= n; ++i) {
		cin >> str;
		for (int j = 1; j <= m; ++j) {
			temp = str[j - 1] - '0';
			input[i][j] = temp;
		}
	}
	for (int i = 1; i <= n; ++i) {
		dp[i][1] = input[i][1];
		answer = max(answer, dp[i][1]);
	}
	for (int j = 1; j <= m; ++j) {
		dp[1][j] = input[1][j];
		answer = max(answer, dp[1][j]);
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			if (i == 1 || j == 1) continue; // 이미 다 넣음
			if (!input[i][j]) dp[i][j] = 0;
			else {
				// 바로 왼쪽 D[i][j-1], 바로 위쪽 D[i-1][j], 바로 왼쪽위의 대각선 D[i-1][j-1]
				// 이 세 가지 값 중 가장 작은 값에 의존될 수 밖에 없음. --> 세가지 값 중 가장 작은 값 + 1
				dp[i][j] = min(min(dp[i][j - 1], dp[i - 1][j]), dp[i - 1][j - 1]) + 1; // 간단함..
			}
			answer = max(answer, dp[i][j]);
		}
	}

	cout << answer * answer;
	return 0;
}