#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
const int INF = 100000000;

void make_path(vector<vector<int>>& dp_record, vector<int>& path, int i, int j) {
	if (dp_record[i][j] == INF) { // 바로 갈 수 있음
		//path.push_back(i);
		path.push_back(j);
	}
	else {
		make_path(dp_record, path, i, dp_record[i][j]);
		make_path(dp_record, path, dp_record[i][j], j);
	}
}

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	int n, m;
	cin >> n >> m; // 도시 수(정점), 버스 수(간선)
	int a, b, c;
	vector<vector<int>> dp(n + 1, vector<int>(n + 1, INF));
	vector<vector<int>> dp_record(n + 1, vector<int>(n + 1, INF));
	for (int i = 1; i <= n; ++i) {
		dp[i][i] = 0;
	}
	for (int i = 0; i < m; ++i) {
		cin >> a >> b >> c;
		if (c < dp[a][b]) dp[a][b] = c;
	}
	
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			for (int k = 1; k <= n; ++k) {
				if (dp[j][k] > dp[j][i] + dp[i][k]) {
					dp[j][k] = dp[j][i] + dp[i][k];
					dp_record[j][k] = i;
				}
			}
		}
	}
	// n x n 
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			if (dp[i][j] == INF) cout << "0 ";
			else cout << dp[i][j] << " ";
		}
		cout << "\n";
	}

	// path print
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			if (i == j || dp[i][j]==INF) { // 같거나 갈 수 없거나
				cout << "0\n";
			}
			else if (dp_record[i][j] == INF) { // 바로 갈 수 있음
				cout << "2 " << i << " " << j << "\n";
			}
			else { // 경유
				vector<int> path = {i};
				make_path(dp_record, path, i, j);
				cout << path.size() << " ";
				for (auto& i : path) {
					cout << i << " ";
				}
				cout << "\n";
			}
		}
	}

	cout << "\n";
	return 0;
}