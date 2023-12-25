#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int N, M; cin >> N >> M;
	vector<vector<char>> Map(N, vector<char>(M, 0));
	for (auto& row : Map) {
		for (auto& v : row) {
			cin >> v;
		}
	}

	int rowCnt{}, colCnt{};
	for (int r{}; r < N; ++r) {
		bool chk{};
		for (int c{}; c < M; ++c) {
			if (Map[r][c] == 'X') {
				chk = true;
				break;
			}
		}
		if (!chk) ++rowCnt;
	}
	for (int c{}; c < M; ++c) {
		bool chk{};
		for (int r{}; r < N; ++r) {
			if (Map[r][c] == 'X') {
				chk = true;
				break;
			}
		}
		if (!chk) ++colCnt;
	}
	cout << max(rowCnt, colCnt) << '\n';

	return 0;
}