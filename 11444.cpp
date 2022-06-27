// 행렬의 거듭 제곱
// 1 1 
// 1 0의 거듭 제곱 이용
#include<iostream>
#include<vector>

using std::vector;
vector<vector<long long int>> result_temp;
vector<vector<long long int>> result;

void matrix_mul(vector<vector<long long int>>& A, vector<vector<long long int>>& B) { // AB
	int N = 2;
	vector<vector<long long int>> result_initial(N, vector<long long int>(N, 0));
	result_temp = std::move(result_initial);
	for (int j = 0; j < N; ++j) {
		for (int k = 0; k < N; ++k) {
			for (int l = 0; l < N; ++l) { // 연산 횟수
				result_temp[j][k] += (A[j][l] * B[l][k]) % 1000000007;
			}
			result_temp[j][k] %= 1000000007;
		}
	}
}

vector<vector<long long int>>& matrix_multiply(vector<vector<long long int>>& A, long long int n) {
	if (n == 1 || n == 0) return A;
	vector<vector<long long int>> result_half = matrix_multiply(A, n / 2);
	matrix_mul(result_half, result_half);
	result = std::move(result_temp);
	if (n % 2 == 1) {
		matrix_mul(result, A);
		result = std::move(result_temp);
	}
	return result;
}

int main() {
	long long int n;
	std::cin >> n;
	vector<vector<long long int>>A = { {1,1}, {1,0} };
	std::cout << matrix_multiply(A,n - 1)[0][0];
	return 0;
}