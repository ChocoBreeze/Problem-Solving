#include<iostream>
#include<vector>

using std::vector;

int count = 0;

void N_queens(vector<vector<int>>& chessboard, int Q_cnt) {
	if (Q_cnt == chessboard.size()) {
		count++; 
		return;
	}

	for (int i = 0; i < chessboard.size(); ++i) { // 하나의 행에서 위치 찾기
		if (chessboard[Q_cnt][i] == 0) {
			int chk_column = 0, chk_diagonal = 0;
			for (int j = 0; j < chessboard.size(); ++j) { // column check
				if (chessboard[j][i] == 1) chk_column = 1;
			}
			if (chk_column == 1) continue;
			for (int j = 0; j < Q_cnt; ++j) { // diagonal check
				if ((i - (Q_cnt - j) >= 0 && chessboard[j][i - (Q_cnt - j)] == 1) ||
					(i + (Q_cnt - j) < chessboard.size() && chessboard[j][i + (Q_cnt - j)] == 1)) { // 위 쪽 대각선
					chk_diagonal = 1;
				}
				if (Q_cnt + j + 1 < chessboard.size()) {
					if ((i - (Q_cnt - j) >= 0 && chessboard[Q_cnt + j + 1][i - (Q_cnt - j)] == 1) ||
						(i + (Q_cnt - j) < chessboard.size() && chessboard[Q_cnt + j + 1][i + (Q_cnt - j)] == 1)) // 아래쪽 대각선
						chk_diagonal = 1;
				}
			}
			if (chk_diagonal == 1) continue;
			if (chk_column == 0 && chk_diagonal == 0) {
				chessboard[Q_cnt][i] = 1;
				N_queens(chessboard, Q_cnt + 1);
				chessboard[Q_cnt][i] = 0;
			}
		}
	}
	return;
}

int main() {
	int N;
	std::cin >> N;
	vector<vector<int>> chessboard(N, vector<int>(N,0));
	N_queens(chessboard, 0);
	std::cout << count;
	return 0;
}