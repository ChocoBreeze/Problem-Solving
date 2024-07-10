#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;
int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	int N, t, p;
	cin >> N;
	vector<int> DP(N + 2, 0);
	for (int i = 1; i <= N; ++i) {
		cin >> t >> p;
		if (t + i - 1 > N) continue;
		int m = 0;
		for (int j = 1; j <= i; ++j) {
			m = max(m, DP[j]);
		}
		if(DP[t + i] < m+p) DP[t+i] = m + p;
	}
	int answer = -1;
	for (int i = 1; i <= N + 1; ++i) {
		answer = max(answer, DP[i]);
	}
	cout << answer;
	return 0;
}