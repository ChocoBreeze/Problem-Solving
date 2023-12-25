#include <iostream>
#include <vector>
#include <algorithm> // max

using namespace std;
vector<vector<int>> board, visited;
int n{}, m{};

int DFS(int x, int y) {
	int picSiz{1};

	for (int d{}; d < 4; ++d) {
		int nx = x + "0211"[d] - '1'; // 상하좌우
		int ny = y + "1102"[d] - '1';
		if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
		if (!board[nx][ny]) continue;
		if (!visited[nx][ny]) {
			visited[nx][ny] = 1;
			picSiz += DFS(nx, ny);
		}
	}
	return picSiz;
}

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	cin >> n >> m; // 세로, 가로

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
			if (!visited[x][y]) {
				visited[x][y] = 1;
				picCnt++;
				maxPicSiz = max(maxPicSiz, DFS(x, y));
			}
		}
	}

	cout << picCnt << '\n' << maxPicSiz << '\n';
	return 0;
}