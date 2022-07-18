// bitfield DP
#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

const int INF = 20000000;

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	int N;
	cin >> N;
	const int SIZE = 1 << N; // bitmask
	vector<vector<int>> AM(N, vector<int>(N, 0));
	for (auto& i : AM) {
		for (auto& j : i) {
			cin >> j;
			if (!j) j = INF; // 못 가는 곳
		}
	}
	// V : 현재 도시를 방문하기까지 이미 방문한 도시들의 비트마스크 값
	// D[V][nexti] = min(D[v에서 도시 i를 방문하지 않은 비트마스크 값][i] + W[i][nexti] - i를 방문하지 않은게 아니고 nexti 아닌가?
	vector<vector<int>> dp(SIZE, vector<int>(N, INF));
	dp[1][0] = 0; // 시작 정점 = 1
	for (int v = 1; v < SIZE; ++v) { // 0번 정점 방문은 1번부터 시작
		for (int j = 0; j < N; ++j) { // nexti
			for (int k = 0; k < N; ++k) { // 현재 정점
				dp[v][j] = min(dp[v][j], dp[v ^ (1 << j)][k] + AM[k][j]);
			}
		}
	}
	int answer = 2000000;
	const int ALLVISITED = (1 << N) - 1;
	for (int i = 1; i < N; ++i) {
		answer = min(answer, dp[ALLVISITED][i] + AM[i][0]); // 최종적으로 돌아오는
	}
	cout << answer;
	return 0;
}