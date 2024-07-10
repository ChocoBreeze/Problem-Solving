#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int candyCount(vector<string>& board) {
	int max_cnt = 0, N = board.size();

	for (int i = 0; i < N; ++i) {
		int max_cnt_row = 0, max_cnt_col = 0;
		int cnt_row = 1, cnt_col = 1; // 자기 자신 포함
		char row_last = board[i][0], col_last = board[0][i];
		for (int j = 1; j < N; ++j) {
			if (row_last == board[i][j]) cnt_row++;
			else {
				max_cnt_row = max(max_cnt_row, cnt_row);
				cnt_row = 1;
				row_last = board[i][j];
			}
			if (col_last == board[j][i]) cnt_col++;
			else {
				max_cnt_col = max(max_cnt_col, cnt_col);
				cnt_col = 1;
				col_last = board[j][i];
			}
		}
		max_cnt_row = max(max_cnt_row, cnt_row);
		max_cnt_col = max(max_cnt_col, cnt_col);
		max_cnt = max(max_cnt, max(max_cnt_row, max_cnt_col));
	}

	return max_cnt;
}

int main() {
	cin.tie(NULL)->sync_with_stdio(false);
	int N;
	cin >> N;
	vector<string> board(N, "0"s);
	for (auto& i : board) {
		cin >> i;
	}
	// 아래, 오른쪽 방향으로 바꾸고
	// 개수세기
	int answer = 0, l;
	for (int i = 0; i < N; ++i) {
		l = 0;
		for (int j = 0; j < N; ++j) {
			// vector<string> temp_board(begin(board), end(board));
			if (i == N - 1) {
				if (j != N - 1) {
					// 오른쪽 방향만 진행
					if (board[i][j] != board[i][j + 1]) {
						swap(board[i][j], board[i][j + 1]);
						answer = max(answer, candyCount(board));
						swap(board[i][j], board[i][j + 1]);
					}
				}
			}
			else {
				if (j != N - 1) {
					// 오른쪽 방향 진행
					if (board[i][j] != board[i][j + 1]) {
						swap(board[i][j], board[i][j + 1]);
						answer = max(answer, candyCount(board));
						swap(board[i][j], board[i][j + 1]);
					}
				}
				// 아래 방향 진행
				if (board[i][j] != board[i + 1][j]) {
					swap(board[i][j], board[i + 1][j]);
					answer = max(answer, candyCount(board));
					swap(board[i][j], board[i + 1][j]);
				}
			}
		}
	}
	cout << answer << '\n';

	return 0;
}