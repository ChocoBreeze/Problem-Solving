#include<iostream>
#include<vector>

int main() {
	int N, a, b;
	std::cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	std::vector<std::vector<int>> A;
	for (int i = 0; i <= 30; ++i) {
		std::vector<int> temp(i+1);
		for (int j = 0; j < i+1; ++j) {
			if (j == 0 || j == i) temp[j] = 1;
			else {
				temp[j] = (A[i - 1][j - 1] + A[i - 1][j]);
			}
		}
		A.push_back(temp);
	}
	std::cin >> N;
	for (int i = 0; i < N; ++i) {
		std::cin >> a >> b;
		std::cout << A[b][a] << "\n";
	}
	return 0;
}