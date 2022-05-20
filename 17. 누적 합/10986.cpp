// 숫자 범위 
#include<iostream>
#include<vector>

int main() {
	std::cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	int N, M;
	std::cin >> N >> M; // 구간이 M으로 나눠떨어지는 개수
	std::vector<int> A(N, 0);
	std::vector<long long> accum(N, 0);
	std::vector<long long> cnt(N, 0); // 나머지가 인덱스인 개수
	for (int i = 0; i < N; ++i) {
		std::cin >> A[i];
		if (i == 0) accum[i] = A[i];
		else accum[i] = accum[i - 1] + A[i];
		cnt[accum[i] % M]++;
	}
	long long count = 0;
	for (int i = 0; i < N; ++i) {
		if (cnt[i] == 0) continue;
		if (i == 0) count += (cnt[i] * (cnt[i] + 1)) / 2;
		else count += (cnt[i] * (cnt[i] - 1)) / 2;
	}
	std::cout << count << "\n";
	return 0;
}