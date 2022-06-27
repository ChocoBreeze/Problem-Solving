#include<iostream>
int main() {
	int N, A, B;
	std::cin >> N;
	for (int i = 0; i < N; i++) {
		std::cin >> A >> B;
		std::cout << A+B << std::endl;
	}
	return 0;
}