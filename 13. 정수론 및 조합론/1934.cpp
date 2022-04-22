// 유클리드 공식
#include<iostream>
#include<vector>

int main()
{
	std::cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	int T, N, M, temp_N, temp_M;
	std::cin >> T;
	for (int i = 0; i < T; ++i) {
		std::cin >> N >> M;
		temp_N = N;
		temp_M = M;
		while (1) {
			if (temp_N == 0 || temp_M == 0) break;
			if (temp_N > temp_M) temp_N %= temp_M;
			else temp_M %= temp_N;
		}
		if (temp_N == 0) std::cout << N * M / temp_M << "\n";
		else std::cout << N * M / temp_N << "\n";
	}
	return 0;
}