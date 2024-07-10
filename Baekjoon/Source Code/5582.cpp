#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	string a, b;
	cin >> a >> b;
	vector<vector<int>> dp(a.length() + 1, vector<int>(b.length() + 1, 0));
	int answer = 0;
	for (int i = 1; i <= a.length(); ++i) {
		for (int j = 1; j <= b.length(); ++j) {
			if (a[i - 1] == b[j - 1]) dp[i][j] = dp[i - 1][j - 1] + 1;
			answer = max(answer, dp[i][j]);
		}
	}
	cout << answer;
	return 0;
}