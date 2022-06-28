// dp[i][j] = i ~ j까지 합치는 최소 비용
// dp[i][i+1] = files[i] + files[j]
// dp[i][j] = min(dp[i][k] + dp[k+1][j] + accum_files[j]-accum_files[j]);(i<=k<j)
// 간단히 생각하기.
// https://cocoon1787.tistory.com/317
// https://js1jj2sk3.tistory.com/3
#include<iostream>
#include<vector>
#include<climits> // INT_MAX
#include<algorithm> // std::min

using std::cin;
using std::cout;
using std::vector;
using std::min;

int main() {
	cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	int T, K;
	cin >> T;
	for (int t = 0; t < T; ++t) {
		cin >> K;
		vector<int> files(K + 1, 0);
		vector<int> accum_files(K + 1, 0); //accum_files[i + 1] = files 0~i번째 까지의 합
		vector<vector<int>> dp(K + 1, vector<int>(K + 1));
		for (int j = 1; j <= K; ++j) {
			cin >> files[j];
			accum_files[j] = accum_files[j - 1] + files[j];
		}
		for (int i = 1; i <= K; ++i) { // 시작점에서 몇 개의 파일을 확인하는지.
			for (int j = 1; j <= K - i; ++j) { // 시작점
				dp[j][i + j] = INT_MAX;
				for (int k = j; k < i + j; ++k) { // 범위 나누기 [j][k] + [k+1][i+j]
					dp[j][i + j] = min(dp[j][i + j], dp[j][k] + dp[k + 1][i + j] + accum_files[i + j] - accum_files[j - 1]);
				}
			}
		}
		cout << dp[1][K] << "\n";
	}
	return 0;
}