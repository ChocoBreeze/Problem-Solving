// parametric search, bfs, two pointer
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct coord {
	int x;
	int y;
	coord(int x, int y) : x(x), y(y) {}
};
coord P(0, 0); // 우체국
int N, K_cnt; // N : 2 ~ 50, K_cnt : 집의 개수
vector<string> map;
vector<vector<int>> high;

bool bfs(int lo, int hi) { // [lo, hi] 범위인 목초지를 이용해서 모든 집을 방문할 수 있는가?
	if (high[P.x][P.y] < lo || high[P.x][P.y] > hi) return false;
	vector<vector<bool>> visited(N, vector<bool>(N, false));
	visited[P.x][P.y] = true;
	queue<coord> Q;
	Q.push(coord(P.x, P.y)); // 시작점
	int K_count = 0;
	while (!Q.empty()) {
		coord now = Q.front();
		Q.pop();

		for (int dx = -1; dx <= 1; ++dx) {
			for (int dy = -1; dy <= 1; ++dy) {
				if (dx || dy) { // dx!=0 && dy!=0
					int nx = now.x + dx, ny = now.y + dy;
					if (nx < 0 || ny < 0 || nx >= N || ny >= N) continue; // 범위
					if (visited[nx][ny]) continue; // 이미 감
					if (high[nx][ny] < lo || high[nx][ny] > hi) continue; // 범위 밖
					visited[nx][ny] = true;
					Q.push(coord(nx, ny));
					if (map[nx][ny] == 'K') K_count++;
				}
			}
		}
	}
	if (K_count == K_cnt) return true;
	return false;
}

int main() {
	cin.tie(NULL)->sync_with_stdio(false);
	cin >> N;
	map = vector<string>(N); // map.assign(N, "");
	high.assign(N, vector<int>(N, 0));
	for (int i = 0; i < N; ++i) {
		cin >> map[i];
		for (int j = 0; j < N; ++j) {
			if (map[i][j] == 'P') {
				P.x = i;
				P.y = j;
			}
			if (map[i][j] == 'K') K_cnt++;
		}
	}
	vector<int> highs; //오름차순, 중복 제거한 height
	highs.reserve(N * N);
	for (auto& i : high) {
		for (auto& j : i) {
			cin >> j;
			highs.push_back(j);
		}
	}
	sort(begin(highs), end(highs));
	highs.erase(unique(begin(highs), end(highs)), end(highs));
	// unique의 return : 중복 제거한 마지막
	int answer{ 10000000 };
	auto lo = begin(highs), hi = begin(highs); // two pointer
	while (lo < end(highs) && hi < end(highs)) {
		if (bfs(*lo, *hi)) {
			answer = min(answer, (*hi) - (*lo));
			lo++;
		}
		else hi++;
	}
	cout << answer << '\n';
	return 0;
}