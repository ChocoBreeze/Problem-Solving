#include <iostream>
#include <vector>
#include <utility>

using namespace std;
int N, M, answer{ -1 }; // 세로, 가로, 정답

vector<vector<vector<int>>> noDfsShape{
	{{-1, 0}, { 1,0 }, { 0, 1 }}, // ㅏ
	{ {-1,0}, {1, 0}, {0, -1} }, // ㅓ
	{ {-1, 0}, {0, -1}, {0, 1} }, // ㅗ
	{ {0, -1}, {0, 1}, {1, 0} } // ㅜ
};
vector<vector<int>> board, visited;

struct Coord {
	int x, y;
	Coord(int x, int y) : x(x), y(y) {}
};

void dfs(Coord now, int sum, int cnt) {
	if (cnt == 4) {
		answer = max(answer, sum);
		return;
	}
	for (int d{}; d < 4; ++d) {
		int nx = now.x + "0211"[d] - '1';
		int ny = now.y + "1102"[d] - '1';
		if (nx < 0 || nx >= N || ny < 0 || ny >= M) continue;
		if (visited[nx][ny]) continue;
		visited[nx][ny] = 1;
		dfs(Coord(nx, ny), sum + board[nx][ny], cnt + 1);
		visited[nx][ny] = 0;
	}
}

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	cin >> N >> M;

	board = vector<vector<int>>(N, vector<int>(M, 0));
	for (auto& row : board) {
		for (auto& v : row) {
			cin >> v;
		}
	}

	visited = vector<vector<int>>(N, vector<int>(M, 0));

	for (int n{}; n < N; ++n) {
		for (int m{}; m < M; ++m) {
			visited[n][m] = 1;
			dfs(Coord(n, m), board[n][m], 1);
			visited[n][m] = 0;

			// DFS로만들 수 없는 모양들 = noDfsShape
			for (auto& shape : noDfsShape) { // 모양별로
				int sum = board[n][m];
				for (auto& dir : shape) {
					auto [dn, dm] = make_pair(dir[0], dir[1]);
					int nN = n + dn, nM = m + dm;
					if (nN < 0 || nN >= N || nM < 0 || nM >= M) break;
					sum += board[nN][nM];
				}
				answer = max(answer, sum);
			}
		}
	}

	cout << answer << '\n';

	return 0;
}