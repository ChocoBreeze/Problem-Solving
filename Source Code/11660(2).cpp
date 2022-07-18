// 조금 더 간소하게 가능.
#include <iostream>
#include <vector>

using namespace std;

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	int N, M;
	cin >> N >> M;
	int temp;
	vector<vector<int>> sum(N + 1,vector<int>(N + 1,0));
	for (int i = 1; i <= N;++i) {
		for (int j = 1; j <= N; ++j) {
			cin >> temp;
			sum[i][j] = sum[i][j - 1] + sum[i - 1][j] - sum[i - 1][j - 1] + temp;
		}
	}
	for (int i = 0; i < M; ++i) {
		int sx, sy, ex, ey;
		cin >> sx >> sy >> ex >> ey;
		cout << sum[ex][ey] - sum[ex][sy-1] - sum[sx-1][ey] + sum[sx-1][sy-1] << "\n";
	}
	return 0;
}