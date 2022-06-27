#include<iostream>
int main() {
	int A, B;
	std::cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	while (1) {
		std::cin >> A >> B;
		if (std::cin.eof()) break;
		std::cout << A + B << "\n";
	}
	return 0;
}