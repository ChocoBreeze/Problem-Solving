#include <iostream>
#include <vector>

using namespace std;
constinit const int SIZE = 101;

struct Robot {
	int x, y, dir;
	Robot(int x, int y, int dir) : x(x), y(y), dir(dir) {}
};

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);

	vector<vector<int>> Map(SIZE, vector<int>(SIZE, 0));
	int N{}; cin >> N; // 드래곤 커브 개수
	for (int n{}; n < N; ++n) {
		int x{}, y{}, d{}, g{}; cin >> y >> x >> d >> g;

		vector<int> dirs{ d };
		// 상하좌우(1320)
		// RULU(0121) + LDLU(2321) (3번째 그림)
		for (int gen{}; gen < g; ++gen) {
			vector<int> nextDir(dirs);
			for (auto it = rbegin(dirs); it != rend(dirs); ++it) {
				nextDir.push_back(((*it) + 1) % 4);
			}
			dirs.swap(nextDir);
		}

		Map[x][y] = 1;
		for (int& dir : dirs) {
			int nx = x + "1012"[dir] - '1', ny = y + "2101"[dir] - '1';
			Map[nx][ny] = 1;
			x = nx, y = ny;
		}
	}

	int answer{};
	for (int x{}; x < SIZE - 1; ++x) {
		for (int y{}; y < SIZE - 1; ++y) {
			if (Map[x][y] && Map[x][y + 1] && Map[x + 1][y] && Map[x + 1][y + 1]) ++answer;
		}
	}
	cout << answer << '\n';

	return 0;
}