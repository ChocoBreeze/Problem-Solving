// 행렬 2개 분할 아이디어는 동일.
// dp[j][i+j] = min(dp[j][k] + dp[k+1][i+j] + matrix[j][0] *
// 점화식 생각하기 - 혼자 복잡하게 생각하지 말기..
// https://cocoon1787.tistory.com/318

#include<iostream>
#include<vector>
#include<climits> // INT_MAX
#include<algorithm> // std::min

struct matrix {
	int row;
	int column;
	matrix(int r, int c) : row(r), column(c) {}
};

using std::vector;
using std::cin;
using std::cout;
using std::min;

int main() {
	cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	int N, r, c;
	cin >> N;
	vector<matrix> matrices(N + 1, matrix(0, 0));
	vector<vector<int>> dp(N + 1, vector<int>(N + 1, 0));
	for (int i = 1; i <= N; ++i) {
		cin >> r >> c;
		matrices[i].column = c;
		matrices[i].row = r;
	}

	for (int i = 1; i <= N; ++i) { // 구간
		for (int j = 1; j <= N - i; ++j) { // 시작점
			dp[j][i + j] = INT_MAX;
			for (int k = j; k < i + j; ++k) {
				dp[j][i + j] = min(dp[j][i + j], dp[j][k] + dp[k + 1][i + j] + matrices[j].row * matrices[k].column * matrices[i + j].column);
			}
		}
	}
	cout << dp[1][N];
	return 0;
}