#include<iostream>

int hansu(int N) {
	if (N < 100) return N; // 100 미만은 다 한수
	int cnt = 99, first,second,third;
	for (int i = 100; i <= N; i++) {
		if (i == 1000) break;
		first = i / 100;
		second = i % 100 / 10;
		third = i % 10;
		if (second * 2 == first + third) cnt++;
	}
	return cnt;
}

int main() {
	int N;
	std::cin >> N;
	std::cout << hansu(N);
	return 0;
}