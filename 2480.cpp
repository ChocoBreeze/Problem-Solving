#include<iostream>
int main() {
	int a, b, c, tmp;
	std::cin >> a >> b >> c;
	if ((a == b) && (b == c)) std::cout << 10000 + a * 1000;
	else if (a == b) std::cout << 1000 + a * 100;
	else if (b == c) std::cout << 1000 + b * 100;
	else if (c == a) std::cout << 1000 + c * 100;
	else {
		if (a > b) { tmp = a; a = b; b = tmp; }
		if (b > c) { tmp = b; b = c; c = tmp; }
		std::cout << c * 100;
	}
	return 0;
}