// https://www.acmicpc.net/problem/11444 같은 문제쓰..
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<long long int>> result_temp;
vector<vector<long long int>> result;

void matrix_mul(vector<vector<long long int>>& A, vector<vector<long long int>>& B) { // AB
	int N = 2;
	vector<vector<long long int>> result_initial(N, vector<long long int>(N, 0));
	result_temp = std::move(result_initial);
	for (int j = 0; j < N; ++j) {
		for (int k = 0; k < N; ++k) {
			for (int l = 0; l < N; ++l) { // 연산 횟수
				result_temp[j][k] += (A[j][l] * B[l][k]) % 1000000;
			}
			result_temp[j][k] %= 1000000;
		}
	}
}

vector<vector<long long int>>& matrix_multiply(vector<vector<long long int>>& A, long long int n) {
	if (n == 1 || n == 0) return A;
	vector<vector<long long int>> result_half = matrix_multiply(A, n / 2);
	matrix_mul(result_half, result_half);
	result = move(result_temp);
	if (n % 2 == 1) {
		matrix_mul(result, A);
		result = move(result_temp);
	}
	return result;
}

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	// long long : ~ 9,223,372,036,854,775,807(920경) (n의 범위 커버 가능)
	long long n;
	cin >> n; 
	// n ~ 1,000,000,000,000,000,000(100경!) - 무지막지하다!
	// logn ~ 59.79(밑 = 2) 엄청 줄어 든다!
	vector<vector<long long int>> A = { {1,1},{1,0} };
	cout << matrix_multiply(A, n - 1)[0][0];
	return 0;
}