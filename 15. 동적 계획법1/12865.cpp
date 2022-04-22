// dp[i][w] : 최초 i개의 물건 중에서 무게가 w를 넘지 않도록 고른 가격 총합의 최대값
// 2D로 확장
// 선택 유무 
#include<vector>
#include<iostream>
int main() {
	int N, K;
	std::cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	std::cin >> N >> K;
	std::vector<int> weight(N, 0);
	std::vector<int> value(N, 0);
	std::vector<std::vector<int>> dp(N + 1, std::vector<int>(K + 1, 0));
	for (int i = 0; i < N; ++i) {
		std::cin >> weight[i] >> value[i];
	}
	for (int i = 0; i < N; ++i) {
		for (int w = 1; w <= K; ++w) { // 넘지 않는 무게 w
			if (w - weight[i] >= 0) { // i번째 물건 선택
				dp[i + 1][w] = dp[i + 1][w] > dp[i][w - weight[i]] + value[i] ? dp[i + 1][w] : dp[i][w - weight[i]] + value[i];
			}
			// i 번째 물건 선택 x
			dp[i + 1][w] = dp[i + 1][w] > dp[i][w] ? dp[i + 1][w] : dp[i][w];
		}
	}
	std::cout << dp[N][K];
	return 0;
}