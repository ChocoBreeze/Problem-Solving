#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int N{};
vector<vector<int>> DP, board;

int DFS(int x, int y) {
	int ret{};
	for (int d{}; d < 4; ++d) {
		int nx = x + "2011"[d] - '1';
		int ny = y + "1120"[d] - '1';
		if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
		if (board[nx][ny] <= board[x][y]) continue;
		if (DP[nx][ny]) ret = max(ret, DP[nx][ny]);
		else ret = max(ret, DFS(nx, ny));
	}
	return DP[x][y] = ret + 1;
}

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	cin >> N;
	board = vector(N, vector<int>(N, 0));
	DP = vector(N, vector<int>(N, 0));

	for (auto& row : board) {
		for (int& v : row) {
			cin >> v;
		}
	}

	int answer{};
	for (int x{}; x < N; ++x) {
		for (int y{}; y < N; ++y) {
			if (DP[x][y] == 0) {
				answer = max(answer, DFS(x, y));
			}
		}
	}
	cout << answer << '\n';

	return 0;
}