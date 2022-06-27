#include<iostream>
#include<vector>

void backtracking(std::vector<std::vector<std::vector<int>>>& w) {
	for (int i = 0; i < 21; ++i) {
		for (int j = 0; j < 21; ++j) {
			for (int k = 0; k < 21; ++k) {
				if (i == 0 || j == 0 || k == 0) w[i][j][k] = 1;
				else if (i < j && j < k) w[i][j][k] = w[i][j][k - 1] + w[i][j - 1][k - 1] - w[i][j - 1][k];
				else w[i][j][k] = w[i - 1][j][k] + w[i - 1][j - 1][k] + w[i - 1][j][k - 1] - w[i - 1][j - 1][k - 1];
			}
		}
	}
}

int main() {
	std::cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	
	int a, b, c;
	std::vector<std::vector<std::vector<int>>> w(21, std::vector<std::vector<int>>(21, std::vector<int>(21,0)));
	backtracking(w);
	while(1) {
		std::cin >> a >> b >> c;
		if (a == -1 && b == -1 && c == -1) break;
		std::cout << "w(" << a << ", " << b << ", " << c << ") = ";
		if (a <= 0 || b <= 0 || c <= 0) std::cout << w[0][0][0] << "\n";
		else if (a > 20 || b > 20 || c > 20) std::cout << w[20][20][20] << "\n";
		else std::cout << w[a][b][c] << "\n";
	}
	return 0;
}