// dp[i][j] = (A[i]==A[j] && dp[i+1][j-1]) ? true:false;
// 간단히 생각하기~
#include<iostream>
#include<vector>
using std::cout;
using std::cin;
using std::vector;

int main() {
	cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	int N;
	cin >> N;
	vector<int> A(N + 1, 0);
	vector<vector<bool>> dp(N + 1, vector<bool>(N + 1, false));
	for (int i = 1; i <= N; ++i) {
		cin >> A[i];
		dp[i][i] = true;
	}
	// dp 채우기 dp[i][j] : i~j까지가 회문인지
	for (int i = 1; i <= N; ++i) { // 간격
		for (int j = 1; j + i <= N; ++j) { // 시작점
			if (i == 1 && A[j] == A[j + i]) {
				dp[j][j + i] = true;
			}
			else if (A[j] == A[j + i] && dp[j + 1][j + i - 1]) {
				dp[j][j + i] = true;
			}
		}
	}
	int M, a, b;
	cin >> M;
	for (int i = 0; i < M; ++i) {
		cin >> a >> b;
		// 회문인지 check
		cout << dp[a][b] << "\n";
	}
	return 0;
}