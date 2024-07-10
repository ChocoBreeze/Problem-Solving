#include <iostream>
#include <vector>

using namespace std;

struct Robot {
	int x, y, dir;
	Robot(int x, int y, int dir) : x(x), y(y), dir(dir) {}
};

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);

	int N{}, M{}; cin >> N >> M;

	Robot r(0, 0, 0);
	cin >> r.x >> r.y >> r.dir;

	vector<vector<int>> Map(N, vector<int>(M, 0));
	for (auto& row : Map) {
		for (auto& v : row) {
			cin >> v;
		}
	}
	int answer{};
	while (1) {
		if (Map[r.x][r.y] == 0) {
			Map[r.x][r.y] = 2;
			++answer;
		}
		
		// 4방향 쓰레기 확인
		int cnt{};
		for (int d{}; d < 4; ++d) {
			int nx = r.x + "2011"[d] - '1';
			int ny = r.y + "1120"[d] - '1';
			if (nx < 0 || nx >= N || ny < 0 || ny >= M) continue;
			if (Map[nx][ny] == 0) ++cnt;
		}

		if (cnt == 0) {
			// 바라보는 방향을 유지한 채로 한 칸 후진할 수 있다면 한 칸 후진하고 1번으로 돌아간다.
			// 바라보는 방향의 뒤쪽 칸이 벽이라 후진할 수 없다면 작동을 멈춘다.
			int ndir = r.dir ^ 2; // 북동남서 순으로 (뒤 방향)
			int nx = r.x + "0121"[ndir] - '1';
			int ny = r.y + "1210"[ndir] - '1';
			if (nx < 0 || nx >= N || ny < 0 || ny >= M) break;
			if (Map[nx][ny] == 1) break; // 벽
			r.x = nx, r.y = ny; // 한 칸 후진
		}
		else {
			// 반시계 방향으로 90도 회전한다.
			// 바라보는 방향을 기준으로 앞쪽 칸이 청소되지 않은 빈 칸인 경우 한 칸 전진한다.
			while (1) { // 어차피 한 번 회전하고 돌아가도 다시 회전하러 와야 함..
				// 북동남서 기준
				int ndir = (r.dir + 3) & 3;
				int nx = r.x + "0121"[ndir] - '1';
				int ny = r.y + "1210"[ndir] - '1';
				if (nx < 0 || nx >= N || ny < 0 || ny >= M) continue;
				if (Map[nx][ny] == 0) {
					r = { nx,ny,ndir };
					break;
				}
				r.dir = ndir;
			}
		}
	}

	cout << answer << '\n';

	return 0;
}