#include <iostream>
#include <vector>
#include <queue>
#include <utility>

using namespace std;

vector<int> dx = { -1,1,0,0 };
vector<int> dy = { 0,0,-1,1 };

const int INF = 100000000l;

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	int M, N;
	cin >> M >> N; // 가로 세로
	vector<vector<int>> map(N, vector<int>(M, 0));
	char input;
	for (int n = 0; n < N; ++n) {
		for (int m = 0; m < M; ++m) {
			cin >> input;
			map[n][m] = input - '0';
		}
	}
	vector<vector<int>> answer(N, vector<int>(M, INF));
	queue<pair<int, int>> Q;
	Q.push(make_pair(0, 0));
	answer[0][0] = 0;
	while (!Q.empty()) {
		pair<int, int> now = Q.front();
		Q.pop();
		for (int i = 0; i < 4; ++i) {
			int nx = now.first + dx[i], ny = now.second + dy[i];
			if (nx >= 0 && nx < N && ny >= 0 && ny < M) {
				if (map[nx][ny] == 0) {
					if (answer[nx][ny] > answer[now.first][now.second]) {
						answer[nx][ny] = answer[now.first][now.second];
						Q.push(make_pair(nx, ny));
					}
				}
				else {
					if (answer[nx][ny] > answer[now.first][now.second] + 1) {
						answer[nx][ny] = answer[now.first][now.second] + 1;
						Q.push(make_pair(nx, ny));
					}
				}
			}
		}
	}
	cout << answer[N - 1][M - 1];
	return 0;
}