// dfs - cycle - 재방문 체크 - 시간
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

vector<int> dx = { -1,1,0,0 };
vector<int> dy = { 0,0,-1,1 };

int N, M; // 세로 가로
bool is_cycle = false;

int dfs(vector<string>& m, vector<vector<int>>& dp, int x, int y) {
	// dfs 
	// 방문 체크
	// -1 = 미방문, -2 = 방문중, 특정 값 = 방문 완료 --> dp!
	int count = 0;
	if (dp[x][y] == -1) {
		dp[x][y] = -2;
		for (int i = 0; i < 4; ++i) {
			int new_x = x + dx[i] * (m[x][y] - '0');
			int new_y = y + dy[i] * (m[x][y] - '0');
			if (new_x >= 0 && new_x < N && new_y >= 0 && new_y < M) {
				if (m[new_x][new_y] != 'H') {
					count = max(count, dfs(m, dp, new_x, new_y) + 1);
				}
			}
		}
		dp[x][y] = count;
		return count;
	}
	else if (dp[x][y] == -2) { // dfs 탐색 중 방문한 경우
		is_cycle = true;
		return 0;
	}
	else { // 이미 방문 완료된 정점
		return dp[x][y];
	}
}

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	cin >> N >> M;
	vector<string> m;
	vector<vector<int>> dp(N, vector<int>(M, -1));
	for (int i = 0; i < N; ++i) {
		string str;
		cin >> str;
		m.push_back(str);
	}
	int answer = dfs(m, dp, 0, 0);

	if (is_cycle) cout << -1;
	else cout << answer + 1; // 마지막 던지기
	return 0;
}