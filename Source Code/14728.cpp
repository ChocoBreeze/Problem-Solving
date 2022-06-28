#include<iostream>
#include<vector>
#include<algorithm>

using std::cin;
using std::cout;
using std::vector;
using std::max;

int main() {
	cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	int N, T;
	cin >> N >> T;
	vector<int> w(N, 0), s(N, 0);
	for (int i = 0; i < N; ++i) {
		cin >> w[i] >> s[i];
	}
	// 100 * 10000 = 1000000
	vector<int> dp(T + 1);
	for (int i = 0; i < N; ++i) {
		vector<int> dp_(T + 1);
		for (int j = 0; j <= T; ++j) {
			dp_[j] = dp[j];
			if (j >= w[i]) dp_[j] = max(dp_[j], dp[j - w[i]] + s[i]);
		}
		dp = std::move(dp_);
	}
	cout << dp[T];
	return 0;
}