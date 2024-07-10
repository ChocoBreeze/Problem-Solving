#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> dx = { -1,1,0,0 };
vector<int> dy = { 0,0,-1,1 };

const int INF = 100000000l;

int dfs(vector<vector<int>>& map, int x, int y) {
	int count = 1; // 자신
	map[x][y] = -1; // 방문 체크
	for (int i = 0; i < 4; ++i) {
		int nx = x + dx[i], ny = y + dy[i];
		if (nx >= 0 && nx < map.size() && ny >= 0 && ny < map[0].size()) {
			if (map[nx][ny] == 0) {
				count += dfs(map, nx, ny);
			}
		}
	}
	return count;
}

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	int M, N, K;
	cin >> M >> N >> K; // M
	vector<vector<int>> map(N, vector<int>(M, 0));
	for (int k = 0; k < K; ++k) {
		int a, b, c, d;
		cin >> a >> b >> c >> d;
		for (int i = a; i < c; ++i) {
			for (int j = b; j < d; ++j) {
				map[i][j]++;
			}
		}
	}
	vector<int> answer;
	for (int m = 0; m < N; ++m) {
		for (int n = 0; n < M; ++n) {
			if (map[m][n] == 0) {
				answer.push_back(dfs(map, m, n));
			}
		}
	}
	cout << answer.size() << "\n";
	sort(begin(answer), end(answer));
	for (auto& a : answer) {
		cout << a << " ";
	}
	return 0;
}