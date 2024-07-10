// weight로 접근하지 말고 cost로 접근하자!
// 메모리 초과 - 2D
// 시간 초과 - 1D
// dp[i][j] : cost 합이 j내로 가장 많이 메모리 확보하기
#include<iostream>
#include<vector>
#include<algorithm> // max
#include<utility> // move
#include<climits> // INT_MAX

using std::move;
using std::cout;
using std::cin;
using std::vector;
using std::max;

int main() {
	cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	int N, M, cost_sum = 0, answer = INT_MAX;
	cin >> N >> M;
	vector<int> weights(N,0);
	vector<int> costs(N,0);
	for (int i = 0; i < N; ++i) {
		cin >> weights[i];
	}
	for (int i = 0; i < N; ++i) {
		cin >> costs[i];
		cost_sum += costs[i];
	}

	vector<int> dp(cost_sum + 1, 0); // 2D 메모리 초과
	for (int i = 0; i < N; ++i) {
		vector<int> dp_temp(cost_sum + 1, 0);
		for (int j = 1; j <= cost_sum; ++j) {
			if (j - costs[i] >= 0) {
				dp_temp[j] = max(dp_temp[j], dp[j - costs[i]] + weights[i]); // i번째 물건 선택
			}
			dp_temp[j] = max(dp_temp[j], dp[j]); // i번째 물건 선택 x
			if (dp_temp[j] >= M && answer>j) { // 처음 넘어가면 바로 최적인 곳.
				answer = j;
			}
		}
		dp = std::move(dp_temp);
	}
	cout << answer;
	return 0;
}