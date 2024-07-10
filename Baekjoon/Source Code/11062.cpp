// �� �� ���⿡�� Ǯ ���� ����.
// https://chb2005.tistory.com/131?category=1030494
// �̷� DP�� �ֱ���...
/*
dp table
dp[i][j] : i ~ j ������ ī�尡 ���� ��, �ٿ찡 ���� �� �ִ� �ִ� ����.
�ٿ��� ������ ��) ī�� ���� �� �ʿ�
dp[i][j] = max(card[j] + dp[i][j-1], card[i] + dp[i+1][j])
����� ������ ��) ī�� ���� �� ��� X
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
		// ������ ���ʰ� ���������� ���� ���� �ٸ���.
		vector<vector<int>> dp(N, vector<int>(N, 0));
		if (N & 1) { // Ȧ�� - �������� �ٿ�
			for (int i{}; i < N; ++i) dp[i][i] = cards[i];
		}

		int turn{ N - 1 };
		for (int interval{ 1 }; interval < N; ++interval) { // or turn > 0
			// ������ -> dp[0][N-1]
			for (int s{}; s + interval < N; ++s) {
				if (turn & 1) { // �ٿ��� ����
					dp[s][s + interval] = max(cards[s] + dp[s + 1][s + interval], dp[s][s + interval - 1] + cards[s + interval]);
				}
				else { // ����� ����
					dp[s][s + interval] = min(dp[s + 1][s + interval], dp[s][s + interval - 1]);
				}
			}
			turn--;
		}
		cout << dp[0][N - 1] << '\n';
	}

	return 0;
}