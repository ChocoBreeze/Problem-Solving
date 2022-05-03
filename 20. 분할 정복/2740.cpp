#include<iostream>
#include<vector>
int main() {
	int N, M, K;
	std::cin >> N >> M;
	using std::vector;
	vector<vector<int>> A(N, vector<int>(M, 0));
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			std::cin >> A[i][j];
		}
	}
	std::cin >> M >> K;
	vector<vector<int>> B(M, vector<int>(K, 0));
	for (int i = 0; i < M; ++i) {
		for (int j = 0; j < K; ++j) {
			std::cin >> B[i][j];
		}
	}
	vector<vector<int>> result(N, vector<int>(K, 0));
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < K; ++j) {
			for (int k = 0; k < M; ++k) { // 연산 횟수
				result[i][j] += A[i][k] * B[k][j];
			}
		}
	}
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < K; ++j) {
			std::cout << result[i][j] << " ";
		}
		std::cout << "\n";
	}
	return 0;
}