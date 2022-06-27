#include<iostream>
#include<vector>
int main() {
	int T, N;
	std::cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	std::cin >> T;
	std::vector<unsigned long long int> tri(100, 1);
	tri[3] = tri[4] = 2;
	for (int i = 5; i < 100; ++i) {
		tri[i] = tri[i - 1] + tri[i - 5];
	}
	for (int i = 0; i < T; ++i) {
		std::cin >> N;
		std::cout << tri[N - 1] << "\n";
	}
	return 0;
}