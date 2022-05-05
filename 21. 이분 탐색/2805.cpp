//parametric search
#include<vector>
#include<iostream>
#include<limits.h>
int main() {
	std::cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	int N;
	long long int M, max = 1, min=1, mid = 0, length;
	std::cin >> N >> M;
	std::vector<long long int> trees(N,0);
	for (int i = 0; i < N; ++i) {
		std::cin >> trees[i];
		if (max < trees[i]) max = trees[i];
	}
	// upper_bound
	while (min < max) {
		mid = min + (max - min) / 2;
		length = 0;
		for (int i = 0; i < N; ++i) {
			length += trees[i] - mid > 0 ? trees[i] - mid : 0;
		}
		if (length <= M) max = mid;
		else min = mid + 1;
	}
	length = 0;
	for (int i = 0; i < N; ++i) {
		length += trees[i] - max > 0 ? trees[i] - max : 0;
	}
	if (length == M) std::cout << max;
	else std::cout << max - 1;
	return 0;
}