// 많이 틀림
//parametric search
#include<vector>
#include<iostream>
#include<limits.h>
int main() {
	std::cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	long long int cnt, min = 1, max = -1, mid, K, N;
	std::cin >> K >> N;
	std::vector<long long int> numbers(K,0);
	for (int i = 0; i < K; ++i) {
		std::cin >> numbers[i];
		if (max < numbers[i]) max = numbers[i];
	}
	//max = INT_MAX;
	// N + 1개를 만드는 lower_bound
	while (min<max) {
		mid = min + (max - min) / 2;
		cnt = 0;
		for (int i = 0; i < K; ++i) {
			cnt += numbers[i] / mid;
		}
		if (cnt <= N - 1) max = mid;
		else min = mid + 1;
	}
	cnt = 0;
	for (int i = 0; i < K; ++i) {
		cnt += numbers[i] / min;
	}
	if (cnt == K) std::cout << min;
	else std::cout << min - 1;
	return 0;
}