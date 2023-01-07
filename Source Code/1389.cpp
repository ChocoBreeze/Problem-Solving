// floyd-warshall
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	int N, M, a, b;
	cin >> N >> M;
	vector<vector<int>> Am(N + 1, vector<int>(N+1, 200)); // 1 ~ N
	for (int n = 0; n < N; ++n) {
		Am[n][n] = 0;
	}
	for (int m = 0; m < M; ++m) {
		cin >> a >> b;
		Am[a][b] = 1;
		Am[b][a] = 1;
	}
	for (int k = 1; k <= N; ++k) {
		for (int i = 1; i <= N; ++i) {
			for (int j = 1; j <= N; ++j) {
				Am[i][j] = min(Am[i][j], Am[i][k] + Am[k][j]);
			}
		}
	}
	int min_answer = 200, answer = 0;
	for (int i = 1; i <= N; ++i) {
		int sum = 0;
		for (int j = 1; j <= N; ++j) {
			sum += Am[i][j];
		}
		if (min_answer > sum) {
			min_answer = sum;
			answer = i;
		}
	}
	cout << answer;

	return 0;
}