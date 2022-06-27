#include<iostream>
int main() {
	int N, X, A;
	std::cin >> N >> X;
	for (int i = 0; i < N; i++) {
		std::cin >> A;
		if (A < X) std::cout << A << " ";
	}
	return 0;
}