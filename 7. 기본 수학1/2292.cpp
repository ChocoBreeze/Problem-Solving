#include<iostream>
int main() {
	int N,out;
	std::cin >> N;
	if (N - 1 == 0) { std::cout << 1; return 0; }
	N -= 1;
	for (int i = 1;; i++) {
		N -= i * 6;
		if (N <= 0) { std::cout << i+1; break; }
	}
	return 0;
}