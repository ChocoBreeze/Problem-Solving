// N과 M은 3 이상 300 이하
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct coord {
	int x;
	int y;
	coord(int x, int y) : x(x), y(y) {}
};

int N, M;
vector<int> dx = { -1,1,0,0 };
vector<int> dy = { 0,0,-1,1 };

int count_glaciers(vector<vector<int>> map) { // 복사로 가져오기
	int count = 0;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			if (map[i][j] > 0) {
				++count;
				queue<coord> Q;
				map[i][j] = -1;
				Q.push(coord(i, j));
				while (!Q.empty()) {
					coord now = Q.front();
					Q.pop();
					for (int i = 0; i < 4; ++i) {
						int new_x = now.x + dx[i], new_y = now.y + dy[i];
						if (new_x >= 0 && new_x < N && new_y >= 0 && new_y < M) {
							if (map[new_x][new_y] > 0) {
								map[new_x][new_y] = 0;
								Q.push(coord(new_x, new_y));
							}
						}
					}
				}
			}
		}
	}
	return count;
}

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	cin >> N >> M;
	vector<vector<int>> map(N, vector<int>(M, 0));
	queue<coord> g;
	for (int i = 0; i < N;++i) {
		for (int j = 0; j < M;++j) {
			cin >> map[i][j];
			if (map[i][j] != 0) {
				g.push(coord(i, j));
			}
		}
	}
	int answer = 0;
	for (int i = 1;; ++i) {
		if (g.empty()) break; // 남는 빙하가 0
		vector<vector<int>> tmp_map(N, vector<int>(M, 0));
		queue<coord> g_temp;
		while (!g.empty()) {
			coord now = g.front();
			g.pop();
			int count = 0;
			for (int i = 0; i < 4; ++i) {
				int new_x = now.x + dx[i], new_y = now.y + dy[i];
				if (new_x >= 0 && new_x < N && new_y >= 0 && new_y < M) {
					if (map[new_x][new_y] == 0) ++count;
				}
			}
			if (map[now.x][now.y] - count > 0) {
				tmp_map[now.x][now.y] = map[now.x][now.y] - count;
				g_temp.push(coord(now.x, now.y));
			}
		}
		map = move(tmp_map);
		g = move(g_temp);
		if (count_glaciers(map) >= 2) {
			answer = i;
			break;
		}
	}
	cout << answer;
	return 0;
}