#include<iostream>
int main() {
	int A, B;
	std::cin >> A >> B;
	if (A > 0 && B > 0) std::cout << 1;
	else if (A > 0 && B < 0) std::cout << 4;
	else if (A < 0 && B > 0) std::cout << 2;
	else std::cout << 3;
	return 0;
}