// dp[i] = dp[i-2]*3 + dp[i-4]*2 + dp[i-6]*2....+ 2
// https://kosaf04pyh.tistory.com/236
#include<iostream>
#include<vector>

using namespace std;
int main() {
	int n;
	cin >> n;
	vector<int> dp(31, 0); // 초기화 잘 하자.
	dp[0] = 1;
	// dp[4] = dp[2]*3 + 2
	for (int i = 2; i <= 30; i+=2) {
		dp[i] += dp[i - 2] * 3;
		for (int j = i - 4; j >= 0; j -= 2) {
			dp[i] += dp[j] * 2;
		}
	}
	cout << dp[n];
	return 0;
}