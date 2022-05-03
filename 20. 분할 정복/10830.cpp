#include<iostream>
#include<vector>
#include<map>
using std::vector;

vector<vector<int>> result_temp;
vector<vector<int>> result;

void matrix_mul(vector<vector<int>>& A, vector<vector<int>>& B) { // AB
	int N = A.size();
	vector<vector<int>> result_initial(N, vector<int>(N, 0));
	result_temp = std::move(result_initial);
	for (int j = 0; j < N; ++j) {
		for (int k = 0; k < N; ++k) {
			for (int l = 0; l < N; ++l) { // 연산 횟수
				result_temp[j][k] += (A[j][l] * B[l][k]) % 1000;
			}
			result_temp[j][k] %= 1000;
		}
	}
}

vector<vector<int>>& matrix_multiply(vector<vector<int>>& A, long long int B) {
	if (B == 1) return A;
	vector<vector<int>> result_half = matrix_multiply(A, B / 2);
	matrix_mul(result_half, result_half);
	result = std::move(result_temp);
	if (B % 2 == 1) {
		matrix_mul(result, A);
		result = std::move(result_temp);
	}
	return result;
}

int main() {
	int N;
	long long int B;
	std::cin >> N >> B;
	vector<vector<int>> A(N, vector<int>(N, 0));
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			std::cin >> A[i][j];
			A[i][j] %= 1000;
		}
	}
	vector<vector<int>> result = matrix_multiply(A, B);
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			std::cout << result[i][j] << " ";
		}
		std::cout << "\n";
	}
	return 0;
}