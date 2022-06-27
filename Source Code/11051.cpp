#include<iostream>
#include<vector>

int main() {
	int N, K, num = 1, denum = 1;
	std::cin >> N >> K;
	std::vector<std::vector<int>> A;
	for (int i = 0; i <= N; ++i) {
		std::vector<int> temp(i+1);
		for (int j = 0; j < i+1; ++j) {
			if (j == 0 || j == i) temp[j] = 1;
			else {
				temp[j] = (A[i - 1][j - 1] + A[i - 1][j]) % 10007;
			}
		}
		A.push_back(temp);
	}
	std::cout << A[N][K];
	return 0;
}