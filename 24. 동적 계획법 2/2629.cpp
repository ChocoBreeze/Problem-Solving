/*
처음 아이디어 dp[i-1] :앞에서 부터 i개의 추를 사용해서 표현할 수 있는 무게를 매번 갱신
--> 결과 : 메모리 초과

이후 아이디어 dp[i][n] : 앞에서부터 i개의 추를 사용해서 무게 n을 표현 가능한지 여부
https://cocoon1787.tistory.com/360
예쁨.
-2 0 2		-2 0 2
-3 0 3		-5 -3 -2 -1 0 1 2 3 5 -->
-3 0 3		-8 -6 -5 -4 -3 -2 -1 0 1 2 3 4 5 6 8
문제점 : 마이너스인 경우 까지 너무 복잡하게 생각했음.
*/

#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath> // abs

using std::cout;
using std::cin;
using std::vector;
using std::abs;

void DP(vector <vector<bool>>& dp, vector<int>& A, int i, int weight) {
	if (dp[i][weight]) return; // 이미 방문 완료
	dp[i][weight] = true;
	if (i == A.size()) return; // 갈 필요 없음
	DP(dp, A, i + 1, weight + A[i]);		// 구슬의 반대 쪽에 놓기
	DP(dp, A, i + 1, abs(weight - A[i]));	// 구슬 쪽에 놓기
	DP(dp, A, i + 1, weight);		// 놓지 않고 skip
}

int main() {
	cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	int N, M, a;
	cin >> N;
	vector<int> A(N, 0);
	for (int i = 0; i < N; ++i) {
		cin >> A[i];
	}
	vector<vector<bool>> dp(N + 1, vector<bool>(15001, false)); // 최대 무게는 15000
	DP(dp, A, 0, 0); // 시작 index, 시작 무게

	// Query
	cin >> M;
	for (int i = 0; i < M; ++i) {
		cin >> a;
		if (a > 15000 || !dp[N][a]) cout << "N ";
		else cout << "Y ";
	}
	return 0;
}