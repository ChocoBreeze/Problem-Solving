#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
constinit const int TRASH = 1;
vector<vector<int>> Map, visited;
int N, M, answer{}, cnt{};

void DFS(int x, int y) { // 인접한 음식물 쓰레기 카운팅
	visited[x][y] = 1;
	cnt++;

	for (int d{}; d < 4; ++d) {
		int nx = x + "0211"[d] - '1';
		int ny = y + "1102"[d] - '1';
		if (nx < 0 || ny < 0 || nx >= N || ny >= M) continue;
		if (!visited[nx][ny] && Map[nx][ny] == TRASH) {
			DFS(nx, ny);
		}
	}
}

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int K{}; cin >> N >> M >> K; // 세로, 가로

	Map = vector<vector<int>>(N, vector<int>(M, 0));
	visited = vector<vector<int>>(N, vector<int>(M, 0));

	for (int k{}; k < K; ++k) {
		int x{}, y{}; cin >> x >> y;
		Map[x - 1][y - 1] = TRASH;
	}

	for (int x{}; x < N; ++x) {
		for (int y{}; y < M; ++y) {
			if (!visited[x][y] && Map[x][y] == TRASH) {
				cnt = 0;
				DFS(x, y);
				answer = max(answer, cnt);
			}
		}
	}
	cout << answer << '\n';
	return 0;
}