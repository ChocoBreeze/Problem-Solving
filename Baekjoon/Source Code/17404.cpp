#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
constinit const int SIZE{ 3 };
constinit const int INF{ 1 << 30 };

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	int N; cin >> N;

	vector<vector<int>> colors(N, vector<int>(3, 0));
	for (vector<int>& row : colors) {
		for (int& v : row) {
			cin >> v;
		}
	}

	int answer{ INF };
	for (int c{}; c < SIZE; ++c) {
		vector<vector<int>> DP(begin(colors), end(colors));
		DP[0][0] = DP[0][1] = DP[0][2] = INF;
		DP[0][c] = colors[0][c];
		for (int n{ 1 }; n < N; ++n) {
			DP[n][0] += min(DP[n - 1][1], DP[n - 1][2]);
			DP[n][1] += min(DP[n - 1][0], DP[n - 1][2]);
			DP[n][2] += min(DP[n - 1][0], DP[n - 1][1]);
		}

		for (int cc{}; cc < SIZE; ++cc) {
			if (c == cc) continue;
			answer = min(answer, DP[N - 1][cc]);
		}
	}
	cout << answer << '\n';

	return 0;
}