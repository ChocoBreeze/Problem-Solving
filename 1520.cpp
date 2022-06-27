// 단순 dfs - 시간 초과
#include<iostream>
#include<vector>
#include<queue>

using std::cout;
using std::cin;
using std::vector;
using std::queue;

struct coord {
	int x;
	int y;
	coord(int x, int y) : x(x), y(y) {}
};

vector<int> dx = { -1, 1, 0, 0 };
vector<int> dy = { 0, 0, -1, 1 };
int M, N;

int dfs(vector<vector<int>>& maps, vector<vector<int>>& dp, coord now) {
	if (now.x == M - 1 && now.y == N - 1) return 1;
	int& temp = dp[now.x][now.y];
	if (temp != -1) return dp[now.x][now.y];
	temp = 0;
	for (int i = 0; i < 4; ++i) {
		int x = now.x + dx[i];
		int y = now.y + dy[i];
		if (x >= 0 && x < M && y >= 0 && y < N) {
			if (maps[x][y] < maps[now.x][now.y]) {
				temp += dfs(maps, dp, coord(x, y));
			}
		}
	}
	return temp;
}

int main() {
	cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	cin >> M >> N; // 가로, 세로
	vector<vector<int>> maps(M, vector<int>(N, 0));
	vector<vector<int>> dp(M, vector<int>(N, -1));
	for (int i = 0; i < M; ++i) {
		for (int j = 0; j < N; ++j) {
			cin >> maps[i][j];
		}
	}
	cout << dfs(maps, dp, coord(0,0));
	return 0;
}