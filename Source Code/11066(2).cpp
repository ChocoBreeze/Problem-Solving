// https://www.acmicpc.net/board/view/53172
// 이걸 어떻게 생각하지!
#include<iostream>
#include<vector>
#include<climits> // INT_MAX
#include<algorithm> // std::min

using std::cin;
using std::cout;
using std::vector;
using std::min;

int DP(vector<vector<int>>& dp, vector<int>& files, vector<int>& accum, int start, int end) {
	// [start, end]
	if (dp[start][end] != INT_MAX) return dp[start][end];
	int temp = INT_MAX;
	int interval_sum = accum[end + 1] - accum[start]; // 필요함
	for (int i = start; i < end; ++i) {
		temp = min(temp, DP(dp, files, accum, start, i) + DP(dp, files, accum, i + 1, end) + interval_sum);
	}
	dp[start][end] = temp;
	return dp[start][end];
}

int main() {
	cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	int T, K;
	cin >> T;
	for (int i = 0; i < T; ++i) {
		cin >> K;
		vector<int> files(K, 0);
		vector<int> accum_files(K+1, 0); //accum_files[i + 1] = files 0~i번째 까지의 합
		vector<vector<int>> dp(K, vector<int>(K, INT_MAX));
		int answer = INT_MAX;
		for (int j = 0; j < K; ++j) {
			cin >> files[j];
			dp[j][j] = files[j];
			accum_files[j + 1] = accum_files[j] + files[j];
		}
		for (int j = 0; j < K - 1; ++j) { // K개를 (1,K-1), (2, K-2), ... (K-1, 1)개로 분할한 것 중 가장 적은 경우 찾기
			answer = min(answer, DP(dp, files,accum_files, 0, j) + DP(dp, files,accum_files, j+1, K-1)); // 이 때는 interval_sum 필요 없음
		}
		cout << answer << "\n";
	}
	return 0;
}