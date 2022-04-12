#include<iostream>
#include<vector>
int main() {
	std::vector<std::vector<int>> number;
	int T, k, n;
	for (int i = 0; i <= 14; i++) {
		std::vector<int> temp;
		for (int j = 0; j <= 14; j++) {
			if (i == 0) temp.push_back(j);
			else {
				int sum = 0;
				for (int k = 0; k <= j; k++) {
					sum += number[i - 1][k];
				}
				temp.push_back(sum);
			}
		}
		number.push_back(temp);
	}

	std::cin >> T;
	for (int i = 0; i < T; ++i) {
		std::cin >> k >> n;
		std::cout << number[k][n] << std::endl;
	}
	return 0;
}