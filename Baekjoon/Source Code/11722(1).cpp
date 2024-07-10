#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main() {
	int N;
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	cin >> N;
	vector<int> A(N, 0);
	for (auto& i : A) {
		std::cin >> i;
	}
	vector<int> dp(N,1);
	int answer = 1;
	for (int i = 1; i < N; ++i) {
		for (int j = 0; j < i; ++j) {
			if (dp[i] < dp[j] + 1 && A[i] < A[j]) {
				dp[i] = dp[j] + 1;
				answer = max(answer, dp[i]);
			}
		}
	}
	
	std::cout << answer;
	return 0;
}