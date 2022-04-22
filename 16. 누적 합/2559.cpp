// 그냥 더하면 시간 초과
// for문 범위 확인
#include<iostream>
#include<vector>
#include<climits> // INT_MIN
int main() {
	int N, K;
	std::cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	std::cin >> N >> K;
	std::vector<int> numbers(N + 1, 0);
	std::vector<long long int> accum(N + 1, 0);
	for (int i = 1; i <= N; ++i) {
		std::cin >> numbers[i];
		accum[i] = accum[i - 1] + numbers[i];
	}
	long long max = INT_MIN;
	for (int i = 0; i <= N - K; ++i) { 
		if (max < accum[i + K] - accum[i]) max = accum[i + K] - accum[i];
	}
	std::cout << max;
	return 0;
}