#include<iostream>
int main() {
	int A, B;
	std::cin >> A >> B;
	std::cout << std::fixed; // 소수점 고정 표현
	std::cout.precision(10); // 11자리에서 반올림
	std::cout << A / (double)B;
	return 0;
}