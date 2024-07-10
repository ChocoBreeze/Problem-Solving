// 그냥 가장 큰 제곱수부터 빼가기 -> 답이 아님 (반례 12)
// https://yabmoons.tistory.com/526 참고.
#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	int N;
	cin >> N;
	vector<int> dp(N + 1, 100000);
	for (int i = 1; i <= N; ++i) {
		if (sqrt(i) - static_cast<int>(sqrt(i)) == 0) {
			dp[i] = 1;
		}
		else {
			for (int j = 1; j * j < i; ++j) {
				dp[i] = min(dp[i], dp[i-j*j] + 1);
			}
		}
		//cout << i << "\n";
	}
	cout << dp[N];
	return 0;
}