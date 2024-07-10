#include <iostream>
#include <vector>
#include <queue>
#include <algorithm> // max

using namespace std;

struct coord {
	int x, y;
	coord(int x, int y) : x(x), y(y) {}
};

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int n{}, m{}; cin >> n >> m; // 세로, 가로

	vector<vector<int>> board, visited;
	board = vector<vector<int>>(n, vector<int>(m, 0));
	visited = vector<vector<int>>(n, vector<int>(m, 0));
	for (auto& row : board) {
		for (auto& c : row) {
			cin >> c;
		}
	}

	int picCnt{}, maxPicSiz{};
	for (int x{}; x < n; ++x) {
		for (int y{}; y < m; ++y) {
			if (!board[x][y]) continue;
			if (visited[x][y]) continue;
			picCnt++;

			int picSiz{1};
			queue<coord> q;
			q.emplace(x, y);
			visited[x][y] = 1;
			while (!q.empty()) {
				coord now = q.front(); q.pop();
				for (int d{}; d < 4; ++d) {
					int nx = now.x + "0211"[d] - '1';
					int ny = now.y + "1120"[d] - '1';
					if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
					if (!board[nx][ny]) continue;
					if (visited[nx][ny]) continue;
					visited[nx][ny] = 1;
					q.emplace(nx, ny);
					picSiz++;
				}
			}
			maxPicSiz = max(maxPicSiz, picSiz);
		}
	}

	cout << picCnt << '\n' << maxPicSiz << '\n';
	return 0;
}