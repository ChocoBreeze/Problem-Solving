// 유클리드 공식
#include<iostream>
#include<vector>

int cal_gcd(int a, int b) {
	if (a % b == 0) return b;
	return cal_gcd(b, a % b);
}

int main()
{
	std::cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	int N, gcd = 0;
	std::cin >> N;
	std::vector<int> numbers(N, 0);
	for (int i = 0; i < N; ++i) {
		std::cin >> numbers[i];
	}
	for (int i = 1; i < N; ++i) {
		gcd = cal_gcd(numbers[0], numbers[i]);
		std::cout << numbers[0] / gcd << "/" << numbers[i] / gcd << "\n";
	}
	return 0;
}