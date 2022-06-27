#include<iostream>
int factorial(int N) {
	if (N == 0) return 0;
	else if (N == 1) return 1;
	return factorial(N-1) + factorial(N-2);
}
int main() {
	int N;
	std::cin >> N;
	std::cout << factorial(N);
	return 0;
}