#include<iostream>
int main() {
	int a, b, c;
	std::cin >> a >> b >> c;
	if (c-b == 0 || a / (c - b) < 0) std::cout << -1;
	else std::cout << int(a / (c - b)) + 1;
	return 0;
}