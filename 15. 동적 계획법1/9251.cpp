/*
점화식 생각하기
dp[i][j] ← 문자열 S의 i번째까지 문자와 문자열 T의 j번째까지 문자 사이의 LCS 길이

S의 i문자와 T의 j문자를 대응시킬 때
S[i-1] == T[j-1] 그렇다면 chmax(dp[i][j], dp[i-1][j-1]+1)
그게 아니라면 chmax(dp[i][j], dp[i-1][j-1])
　
S의 i 문자 추가
「S 의 최초의 i-1 문자분」과「T 의 최초의 j 문자분」과의 대응에 대해서, S 의 i 문자목을 추가합니다.이 때, 특히 LCS의 길이는 변하지 않기 때문에 다음과 같습니다. chmax(dp[i][j], dp[i-1][j])

T 의 j 문자 추가
「S 의 최초의 i 문자분」과「T 의 최초의 j-1 문자분」과의 대응에 대해서, T 의 j 문자목을 추가합니다.이 때, 특히 LCS의 길이는 변하지 않기 때문에 다음과 같습니다. chmax(dp[i][j], dp[i][j-1])
　
계산량은 O(NM)이 됩니다 (N:S 길이, M:T 길이).
*/
#include<iostream>
#include<string>
#include<vector>
int main() {
	std::string A, B;
	std::cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	std::cin >> A >> B;
	int AL = A.length(), BL = B.length();
	std::vector<std::vector<int>> dp(AL + 1, std::vector<int>(BL + 1, 0));
	for (int i = 0; i <= AL; ++i) {
		for (int j = 0; j <= BL; ++j) {
			int temp = 0;
			if (i > 0 && j > 0) {
				if (A[i-1] == B[j-1]) temp = dp[i - 1][j - 1] + 1;
				else temp = dp[i - 1][j - 1];
			}

			if (i > 0) {
				if (temp < dp[i - 1][j]) temp = dp[i - 1][j];
			}
			if (j > 0) {
				if (temp < dp[i][j - 1]) temp = dp[i][j - 1];
			}
			dp[i][j] = temp;
		}
	}
	std::cout << dp[AL][BL];
	return 0;
}