// 정수 범위 확인!
#include<iostream>
#include<string>
#include<vector>

int main()
{
	std::cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	int N;
	std::cin >> N;
	std::vector<unsigned long long int> distance(N-1, 0);
	std::vector<unsigned long long int> oil(N, 0);
	for (int i = 0; i < N - 1; ++i) {
		std::cin >> distance[i];
	}
	for (int i = 0; i < N; ++i) {
		std::cin >> oil[i];
		if (i != 0 && oil[i] > oil[i - 1]) oil[i] = oil[i - 1];
	}
	unsigned long long int sum = 0;
	for (int i = 0; i < N - 1; ++i) {
		sum += distance[i] * oil[i];
	}
	std::cout << sum;
	return 0;
}