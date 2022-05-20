// divide by zero 주의
#include<iostream>
#include<vector>
int main() {
	int N;
	std::cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	std::cin >> N;
	std::vector<int> answer(N);
	answer[0] = 1;
	answer[1] = 2;
	for (int i = 2; i < N; ++i) {
		answer[i] = (answer[i - 1] + answer[i - 2])%15746;
	}
	std::cout << answer[N-1];
	return 0;
}