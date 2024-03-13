// 4408KB, 56ms
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
		vector building(h,""s);
		queue<coord> sQ, fQ;

		for (int i{}; i < h;++i) {
			cin >> building[i];
			for (int j{}; j < w; ++j) {
				if (building[i][j] == '@') sQ.emplace(i, j);
				else if (building[i][j] == '*') fQ.emplace(i, j);
			}
		}

		auto answer = [&]() {
			for (int t{ 1 }; !sQ.empty(); ++t) {
				// 상근씨 이동 - 현재 갈 수 있는 만큼만
				for (int s{}, e{ static_cast<int>(sQ.size()) }; s < e; ++s) {
					auto [x, y] = sQ.front(); sQ.pop();
					if (building[x][y] == '*') continue; // 이동하자마자 불이 퍼짐..
					for (int d{}; d < 4; ++d) {
						int nx = x + "0211"[d] - '1', ny = y + "1102"[d] - '1';
						if (nx < 0 || ny < 0 || nx >= h || ny >= w) { // 탈출 성공
							return t;
						}
						if (building[nx][ny] == '#') continue; // 벽
						if (building[nx][ny] == '*') continue; // 불
						if (building[nx][ny] == '@') continue; // 이미 감
						building[nx][ny] = '@';
						sQ.emplace(nx, ny);
					}
				}

				// 불 확산 - 현재 갈 수 있는 만큼만
				for (int s{}, e{ static_cast<int>(fQ.size()) }; s < e; ++s) {
					auto [x, y] = fQ.front(); fQ.pop();
					for (int d{}; d < 4; ++d) {
						int nx = x + "0211"[d] - '1', ny = y + "1102"[d] - '1';
						if (nx < 0 || ny < 0 || nx >= h || ny >= w) continue; // 범위 밖
						if (building[nx][ny] == '#') continue; // 벽
						if (building[nx][ny] == '*') continue; // 이미 감
						building[nx][ny] = '*';
						fQ.emplace(nx, ny);
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