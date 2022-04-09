#include<iostream>
int main() {
	int A;
	std::cin >> A;
	if (A >= 90) std::cout << "A";
	else if (A >= 80) std::cout << "B";
	else if (A >= 70) std::cout << "C";
	else if (A >= 60) std::cout << "D";
	else std::cout << "F";
	return 0;
}