#include<iostream>
int main() {
	int N, M;
	std::cout << std::fixed;
	std::cout.precision(3);
	std::cin >> N;
	for (int i = 0; i < N; i++) {
		std::cin >> M;
		double sum = 0;
		int* arr = new int[M];
		for (int j = 0; j < M; j++) {
			std::cin >> arr[j];
			sum += arr[j];
		}
		sum /= M;
		int cnt = 0;
		for (int j = 0; j < M; j++) {
			if (arr[j] > sum) cnt++;
		}
		std::cout << (double)cnt / M * 100 << "%\n";
		delete[] arr;
	}
	return 0;
}