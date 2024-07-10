#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	int N;
	cin >> N;
	vector<int> A(N, 0);
	for (auto& i : A) {
		cin >> i;
	}
	int answer = -1;
	vector<int> dp(N, 0);
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j <= i; ++j) {
			if(dp[i] < A[i]) dp[i] = A[i];
			if (dp[i] < dp[j] + A[i] && A[j] < A[i]) {
				dp[i] = dp[j] + A[i];
			}
			answer = max(answer, dp[i]);
		}
	}
	std::cout << answer;
	return 0;
}