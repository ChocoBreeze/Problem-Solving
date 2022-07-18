// floyd - warshall을 어떻게 생각해낼까..
#include <iostream>
#include <vector>

using namespace std;

const int INF = 1000000000;

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	int N, M;
	cin >> N >> M;
	vector<vector<int>> AM(N + 1, vector<int>(N+1,INF)); // 1 ~ N
	for (int i = 1; i <= N; ++i) {
		AM[i][i] = 0;
	}
	for (int m = 0; m < M; ++m) {
		int a, b;
		cin >> a >> b;
		AM[a][b] = 1;
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
	int answer = 0;
	for (int i = 1; i <= N; ++i) {
		int count = 1;
		for (int j = 1; j <= N; ++j) {
			if (i!=j && (AM[i][j] != INF || AM[j][i] != INF)) {
				++count;
			}
		}
		if (count == N) ++answer;
	}
	cout << answer;
	return 0;
}