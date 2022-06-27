#include<iostream>
#include<vector>

int main() {
	std::cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	int N, M;
	std::cin >> N >> M;
	std::vector<std::vector<int>> table(N, std::vector<int>(N, 0));
	std::vector<std::vector<int>> accum(N, std::vector<int>(N, 0));
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			std::cin >> table[i][j];
			if (j == 0) accum[i][j] = table[i][j];
			else accum[i][j] = accum[i][j - 1] + table[i][j];
		}
	}
	int x1, y1, x2, y2;
	for (int i = 0; i < M; ++i) {
		std::cin >> x1 >> y1 >> x2 >> y2;
		int sum = 0; // 2 2 3 4
		for (int j = x1 - 1; j <= x2 - 1; ++j) {
			sum += accum[j][y2 - 1];
			if (y1 != 1) sum -= accum[j][y1 - 2]; // 앞 부분 빼주기	
		}
		std::cout << sum << "\n";
	}
	return 0;
}