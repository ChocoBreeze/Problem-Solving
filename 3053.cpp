#include<iostream>
const double PI = 3.1415926535897932;
int main() {
	double R;
	std::cin >> R;
	std::cout << std::fixed;
	std::cout.precision(6);
	std::cout << R * R * PI << std::endl;
	std::cout << R * R * 2.000000 << std::endl;
	return 0;
}