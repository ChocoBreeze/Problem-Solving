// 접근 참고: https://source-sc.tistory.com/5
// 비재귀
// 5072KB, 4ms
#include <iostream>
#include <vector>

using namespace std;
constinit const int MOD = 1'000'000'003;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int N{}, K{}; cin >> N >> K;

	vector DP(N + 1, vector<int>(K + 1, 0));
	for (int n{ 1 }; n <= N; ++n) {
		DP[n][1] = n;
		for (int k{ 2 }; ((k << 1) <= n) && k <= K; ++k) {
			if (n == (k << 1)) DP[n][k] = 2;
			else {
				DP[n][k] = (DP[n - 1][k] + DP[n - 2][k - 1]) % MOD;
			}
		}
	}

	cout << DP[N][K] << '\n';

	return 0;
}