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
	std::vector<int> list_accm(N + 1, 1);
	std::vector<int> list_desc(N + 1, 1);
	for (int i = 2; i <= N; ++i) {
		for (int j = 1; j < i; ++j) {
			if (list_accm[i] < list_accm[j] + 1 && A[j] < A[i]) 
				list_accm[i] = list_accm[j] + 1;
		}
	}
	for (int i = N - 1; i >= 1; --i) {
		for (int j = N; j > i; --j) {
			if (list_desc[i] < list_desc[j] + 1 && A[j] < A[i]) 
				list_desc[i] = list_desc[j] + 1;
		}
	}
	for (int i = 1; i <= N; ++i) {
		if (max < list_desc[i] + list_accm[i]) max = list_accm[i] + list_desc[i];
	}
	std::cout << max - 1; // 하나 중복
	return 0;
}