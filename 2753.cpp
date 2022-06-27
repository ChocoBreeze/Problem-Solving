#include<iostream>
int main() {
	int A;
	std::cin >> A;
	if (A%4==0 && (A%100!=0 || A%400==0)) std::cout << "1";
	else std::cout << "0";
	return 0;
}