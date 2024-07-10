#include<iostream>

int main() {
	int N, sum = 0;
	char c;
	std::cin >> N;
	for (int i = 0; i < N; i++) {
		std::cin >> c;
		sum += c - '0';
	}
	std::cout << sum;
	return 0;
}