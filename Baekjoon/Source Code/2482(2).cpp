// 접근 참고: https://everenew.tistory.com/42
// 마지막 답만 다른 방식으로 접근. - 이 방식은 이해가 잘 안 감.. (나중에 다시 보고 이해하길 바람..,)
// 5072KB, 4ms
#include <iostream>
#include <vector>

using namespace std;
constinit const int MOD = 1'000'000'003;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int N{}, K{}; cin >> N >> K;

	// 추가적으로 k=0인 경우의 dp값들은 정답에 도달하였으므로 1로 설정(?)
	// DP[n][1] = n으로 설정
	vector DP(N + 1, vector<int>(K + 1, 0));
	DP[0][0] = 1, DP[0][1] = 0;
	DP[1][0] = 1, DP[1][1] = 1;

	for (int n{ 2 }; n <= N; ++n) {
		DP[n][0] = 1;
		DP[n][1] = n;
		for (int k{ 2 }; k <= K; ++k) {
			DP[n][k] = (DP[n - 1][k] + DP[n - 2][k - 1]) % MOD;
		}
	}

	// cout << DP[N][K] << '\n';
	cout << (DP[N - 3][K - 1] + DP[N - 1][K]) % MOD << '\n';

	return 0;
}