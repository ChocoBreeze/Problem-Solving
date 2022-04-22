// 무작정 3으로 나눈 결과가 제일 작을 것이라 생각함
#include<iostream>
#include<vector>

int main() {
	int N;
	std::cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	std::cin >> N; // 1<=N<=10^6
	std::vector<int> count(N + 1, 0);
	for (int i = 2; i <= N; ++i) {
		int min = 1000000;
		if (i % 3 == 0) {
			if(min > count[i / 3] + 1) min = count[i / 3] + 1;
		}
		if (i % 2 == 0) {
			if(min > count[i / 2] + 1) min = count[i / 2] + 1;
		}
		if (min > count[i - 1] + 1)
			min = count[i - 1] + 1;

		count[i] = min;
	}
	std::cout << count[N];
	return 0;
}