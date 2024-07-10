// Divide And Conquer
#include <iostream>
#include <vector>
#include <utility>

using namespace std;
using ll = long long;
int N; // 크기

vector<vector<int>> result_temp;
vector<vector<int>> result;

void matrix_mul(vector<vector<int>> &A, vector<vector<int>> &B)
{ // AB
	vector<vector<int>> resultInitial(N, vector<int>(N, 0));
	for (int j = 0; j < N; ++j)
	{
		for (int k = 0; k < N; ++k)
		{
			for (int l = 0; l < N; ++l)
			{ // 연산 횟수
				resultInitial[j][k] += (A[j][l] * B[l][k]) % 1000;
			}
			resultInitial[j][k] %= 1000;
		}
	}
	result_temp = move(resultInitial);
}

vector<vector<int>> &matrix_multiply(vector<vector<int>> &A, long long int B)
{
	if (B == 1)
		return A;
	vector<vector<int>> result_half = matrix_multiply(A, B / 2); // Divide And Conquer
	matrix_mul(result_half, result_half);
	result = move(result_temp);
	if (B % 2 == 1)
	{ // A 한 번 더 곱하기
		matrix_mul(result, A);
		result = move(result_temp);
	}
	return result;
}

int main()
{
	long long int B; // 몇 번 제곱해야 하는지
	cin >> N >> B;
	vector<vector<int>> A(N, vector<int>(N, 0));
	for (auto &row : A)
	{
		for (int &v : row)
		{
			cin >> v;
			v %= 1000;
		}
	}

	vector<vector<int>> result = matrix_multiply(A, B);
	for (auto &row : result)
	{
		for (int &v : row)
		{
			cout << v << ' ';
		}
		cout << '\n';
	}
	return 0;
}