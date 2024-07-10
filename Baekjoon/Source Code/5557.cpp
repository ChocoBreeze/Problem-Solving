#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	int N;
	cin >> N;
	vector<int> A(N, 0);
	for (auto& i : A) {
		cin >> i;
	}
	// 어차피 음수는 못 들어가고, 모두 다 9일 때 다 합쳐도 900
	// 또한 최대 개수가 2^63 - 1 -> long long으로 충분
	vector<long long> dp(21, 0); // 0 ~ 20
	dp[A[0]] = 1;
	for (int i = 1; i < N - 1; ++i) { // 첫 원소 마지막 원소 필요 x
		vector<long long> dp_(21, 0); // 1 ~ 20
		for (int j = 0; j <= 20; ++j) {
			if (dp[j] == 0) continue; // 개수가 없다
			int plus = j + A[i], minus = j - A[i];
			if (0 <= plus && plus <= 20) dp_[plus] += dp[j];
			if (0 <= minus && minus <= 20) dp_[minus] += dp[j];
		}
		dp = move(dp_);
	}
	cout << dp[A.back()];
	return 0;
}