#include<iostream>
int main() {
	int T,N;
	bool* check = new bool[10001];
	check[0] = false; check[1] = false;
	for (int i = 2; i <= 10000; i++) {
		check[i] = true;
	}
	for (int i = 2; i <= 10000; i++) {
		if (check[i]) {
			if (i * i > 10001) break;
			for (int j = i * i; j < 10000; j+=i) {
				check[j] = false;
			}
		}
	}
	std::cin >> T;
	for (int i = 0; i < T; i++) {
		std::cin >> N;
		for (int j = N / 2; j >= 2; j--) {
			if (check[j] && check[N - j]) {
				std::cout << j << " " << N - j << "\n";
				break;
			}
		}
	}
	return 0;
}