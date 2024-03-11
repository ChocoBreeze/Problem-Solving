// 접근 참고: https://source-sc.tistory.com/5
// Recursion
// 6000KB, 4ms

#include <iostream>
#include <vector>

using namespace std;
constinit const int MOD = 1'000'000'003;
vector<vector<int>> DP;

int dp(int n, int k) {
	if (n < (k << 1)) return DP[n][k] = 0; // 처리
	else if (k == 1) DP[n][k] = n;
	else if (n == (k << 1)) return DP[n][k] = 2;
	else if (DP[n][k] == -1) { // 미방문
		DP[n][k] = (dp(n - 1, k) + dp(n - 2, k - 1)) % MOD;
	}
	return DP[n][k];
}

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int N{}, K{}; cin >> N >> K;

	DP.assign(N + 1, vector<int>(N + 1, -1));

	cout << dp(N, K) << '\n';

	return 0;
}