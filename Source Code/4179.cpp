// 3236KB, 32ms
#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

struct coord {
	int r, c;
	coord(int r, int c) : r{ r }, c{ c } {}
	coord() = default;
};

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int R{}, C{}; cin >> R >> C;
	vector board(R, ""s);

	queue<coord> jQ, fQ;
	for (int r{}; r < R; ++r) {
		cin >> board[r];
		for (int c{}; c < C; ++c) {
			if (board[r][c] == 'J') jQ.emplace(r, c);
			else if (board[r][c] == 'F') fQ.emplace(r, c);
		}
	}

	for (int day{ 1 };; ++day) {
		if (jQ.empty()) break;
		for (int i{}, sz{ static_cast<int>(jQ.size()) }; i<sz;++i) {
			auto [r, c] = jQ.front(); jQ.pop();
			if (board[r][c] == 'F') continue;
			for (int d{}; d < 4; ++d) {
				int nr = r + "0211"[d] - '1', nc = c + "1102"[d] - '1';
				if (nr < 0 || nc < 0 || nr >= R || nc >= C) {
					cout << day << '\n';
					return 0;
				}
				if (board[nr][nc] == 'F') continue; // 불
				if (board[nr][nc] == '#') continue; // 벽
				if (board[nr][nc] == 'J') continue; // 이미 방문 - 메모리 초과..
				board[nr][nc] = 'J';
				jQ.emplace(nr, nc);
			}
		}

		for (int i{}, sz{ static_cast<int>(fQ.size()) }; i < sz; ++i) {
			auto [r, c] = fQ.front(); fQ.pop();
			for (int d{}; d < 4; ++d) {
				int nr = r + "0211"[d] - '1', nc = c + "1102"[d] - '1';
				if (nr < 0 || nc < 0 || nr >= R || nc >= C) continue; // out of range
				if (board[nr][nc] == 'F') continue; // 이미 방문
				if (board[nr][nc] == '#') continue; // 벽
				board[nr][nc] = 'F';
				fQ.emplace(nr, nc);
			}
		}
	}
	cout << "IMPOSSIBLE\n";
	return 0;
}
