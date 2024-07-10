#include<iostream>
int main() {
	int N;
	std::cin >> N;
	for (int i = 1; i <= 9; i++) {
		std::cout << N << " * " << i << " = " << N * i << std::endl;
	}
	return 0;
}