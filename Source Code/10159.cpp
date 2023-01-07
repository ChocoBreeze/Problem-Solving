#include <iostream>
#include <vector>

using namespace std;

const int INF = 1000000000;

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	int N, M, a, b;
	cin >> N >> M;
	vector<vector<int>> AM(N + 1, vector<int>(N + 1, INF));
	for (int i = 1; i <= N; ++i) {
		AM[i][i] = 0;
	}
	for (int m = 0; m < M; ++m) {
		cin >> a >> b;
		AM[a][b] = 1;
		// AM[b][a] = 1;
	}
	for (int k = 1; k <= N; ++k) {
		for (int i = 1; i <= N; ++i) {
			for (int j = 1; j <= N; ++j) {
				if (AM[i][j] > AM[i][k] + AM[k][j]) {
					AM[i][j] = AM[i][k] + AM[k][j];
				}
			}
		}
	}
	vector<int> answer(N + 1, 0);
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j) {
			if (AM[i][j] == INF && AM[j][i]==INF) answer[i]++;
		}
	}
	for (auto i = answer.begin() + 1; i != answer.end();++i) {
		cout << *i << "\n";
	}
	return 0;
}