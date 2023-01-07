#include <iostream>
#include <vector>

using namespace std;

const int INF = 1000000000;

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	int n, m, r;
	cin >> n >> m >> r;
	vector<int> items(n + 1);
	vector<vector<int>> AM(n + 1, vector<int>(n + 1, INF));
	for (int i = 1; i <= n; ++i) {
		cin >> items[i];
		AM[i][i] = 0;
	}
	int a, b, l;
	for (int i = 0; i < r; ++i) {
		cin >> a >> b >> l;
		AM[a][b] = l;
		AM[b][a] = l;
	}
	for (int k = 1; k <= n; ++k) {
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				if (AM[i][j] > AM[i][k] + AM[k][j]) {
					AM[i][j] = AM[i][k] + AM[k][j];
				}
			}
		}
	}
	int answer = 0;
	for (int i = 1; i <= n; ++i) {
		int sum = 0; // i -> j
		for (int j = 1; j <= n; ++j) {
			if (AM[i][j] <= m) sum += items[j];
		}
		answer = answer > sum ? answer : sum;
	}
	cout << answer;

	return 0;
}