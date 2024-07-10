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
		
		// 4���� ������ Ȯ��
		int cnt{};
		for (int d{}; d < 4; ++d) {
			int nx = r.x + "2011"[d] - '1';
			int ny = r.y + "1120"[d] - '1';
			if (nx < 0 || nx >= N || ny < 0 || ny >= M) continue;
			if (Map[nx][ny] == 0) ++cnt;
		}

		if (cnt == 0) {
			// �ٶ󺸴� ������ ������ ä�� �� ĭ ������ �� �ִٸ� �� ĭ �����ϰ� 1������ ���ư���.
			// �ٶ󺸴� ������ ���� ĭ�� ���̶� ������ �� ���ٸ� �۵��� �����.
			int ndir = r.dir ^ 2; // �ϵ����� ������ (�� ����)
			int nx = r.x + "0121"[ndir] - '1';
			int ny = r.y + "1210"[ndir] - '1';
			if (nx < 0 || nx >= N || ny < 0 || ny >= M) break;
			if (Map[nx][ny] == 1) break; // ��
			r.x = nx, r.y = ny; // �� ĭ ����
		}
		else {
			// �ݽð� �������� 90�� ȸ���Ѵ�.
			// �ٶ󺸴� ������ �������� ���� ĭ�� û�ҵ��� ���� �� ĭ�� ��� �� ĭ �����Ѵ�.
			while (1) { // ������ �� �� ȸ���ϰ� ���ư��� �ٽ� ȸ���Ϸ� �;� ��..
				// �ϵ����� ����
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