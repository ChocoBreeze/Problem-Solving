// counting sort
#include<vector>
#include<iostream>

int main() {
	int N, temp;
	std::cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	std::cin >> N;
	std::vector<int> list(10001, 0);
	for (int i = 0; i < N; ++i) {
		std::cin >> temp;
		++list[temp];
	}
	for (int i = 1; i < 10001; ++i) {
		for (int j = 0; j < list[i]; ++j) {
			std::cout << i << "\n";
		}
	}
	return 0;
}