#include<iostream>
#include<vector>

int main() {
	std::cin.tie(NULL);
	std::ios::sync_with_stdio(false);

	std::vector<std::pair<int, int>> fibonacci;
	fibonacci.push_back(std::make_pair(1, 0));
	fibonacci.push_back(std::make_pair(0, 1));
	for (int i = 2; i <= 40; ++i) {
		fibonacci.push_back(std::make_pair(fibonacci[i - 2].first + fibonacci[i - 1].first, fibonacci[i - 2].second + fibonacci[i - 1].second));
	}
	int N ,tmp;
	std::cin >> N;
	for (int i = 0; i < N; ++i) {
		std::cin >> tmp;
		std::cout << fibonacci[tmp].first << " " << fibonacci[tmp].second << "\n";
	}
	return 0;
}