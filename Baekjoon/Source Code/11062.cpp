// 한 쪽 방향에서 풀 수는 없음.
// https://chb2005.tistory.com/131?category=1030494
// 이런 DP도 있구나...
/*
dp table
dp[i][j] : i ~ j 까지의 카드가 있을 때, 근우가 얻을 수 있는 최대 점수.
근우의 차례일 때) 카드 점수 합 필요
dp[i][j] = max(card[j] + dp[i][j-1], card[i] + dp[i+1][j])
명우의 차례일 때) 카드 점수 합 계산 X
dp[i][j] = min(dp[i][j-1], dp[i+1][j])
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	int T{}; cin >> T;
	while (T--) {
		int N{}; cin >> N;
		vector<int> cards(N, 0);
		for (int& v : cards) cin >> v;
		// 마지막 차례가 누구인지에 따라 시작 다르게.
		vector<vector<int>> dp(N, vector<int>(N, 0));
		if (N & 1) { // 홀수 - 마지막이 근우
			for (int i{}; i < N; ++i) dp[i][i] = cards[i];
		}

		int turn{ N - 1 };
		for (int interval{ 1 }; interval < N; ++interval) { // or turn > 0
			// 마지막 -> dp[0][N-1]
			for (int s{}; s + interval < N; ++s) {
				if (turn & 1) { // 근우의 차례
					dp[s][s + interval] = max(cards[s] + dp[s + 1][s + interval], dp[s][s + interval - 1] + cards[s + interval]);
				}
				else { // 명우의 차례
					dp[s][s + interval] = min(dp[s + 1][s + interval], dp[s][s + interval - 1]);
				}
			}
			turn--;
		}
		cout << dp[0][N - 1] << '\n';
	}

	return 0;
}