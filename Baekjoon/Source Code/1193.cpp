#include<iostream>
int main() {
	int X;
	std::cin >> X;
	for (int i = 1;; i++) {
		if (X-i <= 0) {
			if (i % 2 == 1) std::cout << i + 1 - X << "/" << X;
			else std::cout << X << "/" << i + 1 - X;
			break;
		}
		X -= i;
	}
	return 0;
}