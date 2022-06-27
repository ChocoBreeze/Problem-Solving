#include<iostream>
int main() {
	const int N = 247000;
	bool* check = new bool[N];
	check[0] = check[1] = false;
	for (int i = 2; i < N; i++) {
		check[i] = true;
	}
	for (int i = 2; i < N; i++) {
		if (check[i]) {
			if ((long long)i * i > 247001) break;
			for (int j = i * i; j < N; j += i) {
				check[j] = false;
			}
		}
	}
	int n,cnt;
	while (1) {
		std::cin >> n;
		if (n == 0) break;
		cnt = 0;
		for (int i = n+1; i <= 2 * n; i++) {
			if (check[i]) cnt++;
		}
		std::cout << cnt << std::endl;
	}
	delete[] check;
	return 0;
}