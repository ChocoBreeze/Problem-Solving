#include<iostream>

int main() {
	int N, K, num = 1, denum = 1;
	std::cin >> N >> K;
	for (int i = N; i >= N - K + 1; --i) {
		num *= i;
	}
	for(int i=1;i<=K;++i) {
		denum *= i;
	}
	std::cout << num / denum;
	return 0;
}