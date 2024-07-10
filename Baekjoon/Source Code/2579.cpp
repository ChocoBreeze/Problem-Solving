// 2번 틀림
#include<iostream>
#include<vector>

int main() {
	int N;
	std::cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	std::cin >> N;
	std::vector<int> stair(N + 1, 0);
	std::vector<int> sum(N + 1, 0);
	for (int i = 1; i <= N; ++i) {
		std::cin >> stair[i];
	}
	sum[1] = stair[1];
	sum[2] = stair[1] + stair[2] > stair[2] ? stair[1] + stair[2] : stair[2];
	for (int i = 3; i <= N; ++i) {
		sum[i] = sum[i - 3] + stair[i-1] > sum[i-2] ? sum[i-3] + stair[i-1] : sum[i-2];
		sum[i] += stair[i];
	}
	std::cout << sum[N];
	return 0;
}