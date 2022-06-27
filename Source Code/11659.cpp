// 그냥 더하면 시간 초과
#include<iostream>
#include<vector>
int main() {
	int N, M, start, end;
	long long sum;
	std::cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	std::cin >> N >> M;
	std::vector<int> numbers(N + 1, 0);
	std::vector<long long int> accum(N + 1, 0);
	for (int i = 1; i <= N; ++i) {
		std::cin >> numbers[i];
		accum[i] = accum[i - 1] + numbers[i];
	}

	for (int i = 0; i < M; ++i) {
		std::cin >> start >> end;
		std::cout << accum[end] - accum[start - 1] << "\n";
	}
	return 0;
}