#include<iostream>
int main() {
	int N, min = 2000;
	std::cin >> N;
	if (N % 3 == 0) min = N / 3;
	else if (N % 5 == 0 && min > N / 5) min = N / 5;
	for (int i = 1; i <= N / 5; i++) {
		if ((N - (5 * i)) % 3 == 0 && min > i + (N - (5 * i)) / 3) min = i + (N - (5 * i)) / 3;
	}
	if (min == 2000) std::cout << -1;
	else std::cout << min;
	return 0;
}