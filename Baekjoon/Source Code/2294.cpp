#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	int n, k;
	cin >> n >> k;
	vector<int> coins(n, 0);
	vector<int> dp(k + 1, 100001);
	dp[0] = 0;
	for (auto& i : coins) {
		cin >> i;
		if(i <= k) dp[i] = 1; // 범위 안인 동전만
	}
	sort(begin(coins), end(coins));
	for (int i = 1; i <= k; ++i) {
		if (dp[i] == 1) continue;
		for (int j = 0; j < n; ++j) {
			if (i - coins[j] < 0) continue;
			dp[i] = min(dp[i], dp[i - coins[j]] + 1);
		}
	}
	if (dp[k] == 100001) cout << -1;
	else cout << dp[k];
	return 0;
}