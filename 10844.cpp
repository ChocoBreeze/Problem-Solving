// 마지막 자리수로 점화식 - 생각을 못함!
#include<iostream>
#include<vector>

int main() {
	int N;
	std::cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	std::cin >> N; // 1<=N<=100
	std::vector<std::vector<int>> stair(N, std::vector<int>(10, 0));
	stair[0] = { 0, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
	for (int i = 1; i < N; ++i) {
		stair[i][0] = stair[i - 1][1];
		stair[i][9] = stair[i - 1][8];
		for (int j = 1; j <= 8; ++j) {
			stair[i][j] = (stair[i - 1][j - 1] + stair[i - 1][j + 1]) % 1000000000;
		}
	}
	unsigned long long int sum = 0;
	for (int i = 0; i < 10; ++i) {
		sum += stair[N - 1][i];
	}
	std::cout << sum % 1000000000;
	return 0;
}