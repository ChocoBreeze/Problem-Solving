#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Coord {
	int x, y;
	Coord(int x, int y) : x(x), y(y) {}
};
constinit const int WALL = 0;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int n, m; // 세로, 가로
	cin >> n >> m;

	vector<vector<int>> board(n, vector<int>(m, 0));
	Coord target(0,0); // 시작 지점
	for (int i{}; i < n; ++i) {
		for (int j{}; j < m; ++j) {
			cin >> board[i][j];
			if (board[i][j] == 2) {
				target.x = i, target.y = j;
			}
		}
	}

	vector<vector<int>> visited(n, vector<int>(m, 0));
	visited[target.x][target.y] = 1;
	queue<Coord> q;
	q.emplace(target.x, target.y);
	while (!q.empty()) {
		Coord now = q.front(); q.pop();

		for (int d{}; d < 4; ++d) {
			int nx = now.x + "0211"[d] - '1';
			int ny = now.y + "1102"[d] - '1';
			if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
			if (board[nx][ny] == WALL) continue;
			if (visited[nx][ny]) continue;
			visited[nx][ny] = visited[now.x][now.y] + 1;
			q.emplace(nx, ny);
		}
	}

	for (int i{}; i < n; ++i) {
		for (int j{}; j < m; ++j) {
			if (visited[i][j] == 0) {
				if (board[i][j] == WALL) {
					cout << visited[i][j] << ' '; // 0
				}
				else {
					cout << visited[i][j] - 1 << ' '; // -1
				}
			}
			else cout << visited[i][j] - 1 << ' ';
		}
		cout << '\n';
	}

	return 0;
}