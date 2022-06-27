// 시간초과 주의
#include<iostream>
int main() {
	int M, N;
	std::cin >> M >> N;
	bool* check = new bool[N + 1];
	check[0] = check[1] = false;
	for (int i = 2; i <= N; i++) {
		check[i] = true;
	}
	for (int i = 2; i <= N; i++) {
		if (check[i]) {
			if ((long long)i * i > 1000001) break;
			for (int j = i * i; j <= N; j += i) {
				check[j] = false;
			}
		}
	}
	for (int i = M; i <= N; i++) {
		if (check[i]) std::cout << i << "\n";
	}
	return 0;
}