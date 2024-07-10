#include<iostream>
int factorial(int N) {
	if (N == 0) return 1;
	return N * factorial(N - 1);
}
int main() {
	int N;
	std::cin >> N;
	std::cout << factorial(N);
	return 0;
}