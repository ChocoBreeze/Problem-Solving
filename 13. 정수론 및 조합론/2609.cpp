// 유클리드 공식
#include<iostream>
#include<vector>

int main()
{
	std::cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	int N, M, temp_N, temp_M;
	std::cin >> N >> M;
	temp_N = N;
	temp_M = M;
	while (1) {
		if (temp_N == 0 || temp_M == 0) break;
		if (temp_N > temp_M) temp_N %= temp_M;
		else temp_M %= temp_N;
	}
	if (temp_N == 0) std::cout << temp_M << "\n" << N * (M / temp_M);
	else std::cout << temp_N << "\n" << N * (M / temp_N);

	return 0;
}