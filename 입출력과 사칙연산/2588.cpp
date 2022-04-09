#include<iostream>
int main() {
	int A, B;
	std::cin >> A >> B;
	std::cout << A * (B % 10) << std::endl;
	std::cout << A * ((B / 10) % 10) << std::endl;
	std::cout << A * (B / 100) << std::endl;
	std::cout << A * B;
	return 0;
}