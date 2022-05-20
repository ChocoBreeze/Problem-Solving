// LIS(Longest Increasing Subsequence)
// 다시 보기!
#include<iostream>
#include<vector>

int main() {
	int N, max = 1;
	std::cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	std::cin >> N; // 1<=N<=1000
	std::vector<int> A(N + 1,0);
	for (int i = 1; i <= N; ++i) {
		std::cin >> A[i];
	}
	std::vector<int> list(N + 1, 1);
	for (int i = 2; i <= N; ++i) {
		for (int j = 1; j < i; ++j) {
			if (list[i] < list[j] + 1 && A[j] < A[i]) {
				list[i] = list[j] + 1;
				if (max < list[i]) max = list[i];
			}
		}
	}
	std::cout << max;
	return 0;
}