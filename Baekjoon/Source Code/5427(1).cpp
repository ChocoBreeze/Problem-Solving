// 11036KB, 96ms
// line 67..
#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

struct coord {
	int x{}, y{};
	coord(int x, int y) : x{ x }, y{ y } {}
	coord() = default;
};

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int T{}; cin >> T;

	while (T--) {
		int w{}, h{}; cin >> w >> h;
		vector building(h, ""s);
		queue<coord> sQ, fQ;
		vector fVisited(h, vector(w, 0)); // 불 방문
		vector sVisited(h, vector(w, 0)); // 상근씨 방문

		for (int i{}; i < h; ++i) {
			cin >> building[i];
			for (int j{}; j < w; ++j) {
				if (building[i][j] == '@') {
					sQ.emplace(i, j);
					sVisited[i][j] = 1;
				}
				else if (building[i][j] == '*') {
					fQ.emplace(i, j);
					fVisited[i][j] = 1;
				}
			}
		}

		while (!fQ.empty()) {
			// 불 확산 - 현재 갈 수 있는 만큼만
			for (int s{}, e{ static_cast<int>(fQ.size()) }; s < e; ++s) {
				auto [x, y] = fQ.front(); fQ.pop();
				for (int d{}; d < 4; ++d) {
					int nx = x + "0211"[d] - '1', ny = y + "1102"[d] - '1';
					if (nx < 0 || ny < 0 || nx >= h || ny >= w) continue; // 범위 밖
					if (building[nx][ny] == '#') continue; // 벽
					if (fVisited[nx][ny]) continue; // 이미 감
					fVisited[nx][ny] = fVisited[x][y] + 1;
					fQ.emplace(nx, ny);
				}
			}
		}

		auto answer = [&sQ, &building, &sVisited, &fVisited, h, w]() {
			while(!sQ.empty()) {
				// 상근씨 이동 - 현재 갈 수 있는 만큼만
				for (int s{}, e{ static_cast<int>(sQ.size()) }; s < e; ++s) {
					auto [x, y] = sQ.front(); sQ.pop();
					for (int d{}; d < 4; ++d) {
						int nx = x + "0211"[d] - '1', ny = y + "1102"[d] - '1';
						if (nx < 0 || ny < 0 || nx >= h || ny >= w) { // 탈출 성공
							return sVisited[x][y];
						}
						if (building[nx][ny] == '#') continue; // 벽
						if (fVisited[nx][ny] && sVisited[x][y] + 1 >= fVisited[nx][ny]) continue; // 불보다 빨리 도달 불가능
						// 불이 방문 안 한 곳에 대해서 sVisited가 더 큰 경우 방문을 막아버림.
						// sVisited[x][y] + 1 > fVisited[nx][ny]라고 적는다면 (상근이 도달 후 같은 차례에 불이 도달하는 경우에 대해 처리를 못 함)
						if (sVisited[nx][ny]) continue; // 이미 감
						sVisited[nx][ny] = sVisited[x][y] + 1;
						sQ.emplace(nx, ny);
					}
				}
			}
			return -1; // 탈출 실패
		} ();
		if (answer == -1) cout << "IMPOSSIBLE\n";
		else cout << answer << '\n';
	}
	return 0;
}