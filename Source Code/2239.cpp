#include<iostream>
#include<vector>
#include<utility> // pair
#include<string>

using namespace std;

int chk = 0;

void sdoku(vector<vector<int>>& board, vector<pair<int, int>>& emptyplace, int emptyindex) {
	if (chk == 1 || emptyplace.size() == emptyindex) {
		if (chk == 0) {
			for (int i = 0; i < 9; ++i) {
				for (int j = 0; j < 9; ++j) {
					cout << board[i][j];
				}
				cout << "\n";
			}
		}
		chk = 1;
		return;
	}
	vector<bool> possible_number(9, true);
	int x = emptyplace[emptyindex].first, y = emptyplace[emptyindex].second;
	for (int i = 0; i < 9; ++i) {
		if (board[x][i] != 0) {
			possible_number[board[x][i] - 1] = false; // 가로
		}
		if (board[i][y] != 0) {
			possible_number[board[i][y] - 1] = false; // 세로
		}
	}
	// 3 x 3
	for (int i = (x / 3) * 3; i < (x / 3) * 3 + 3; ++i) {
		for (int j = (y / 3) * 3; j < (y / 3) * 3 + 3; ++j) {
			if (board[i][j] != 0) {
				possible_number[board[i][j] - 1] = false;
			}
		}
	}
	for (int i = 0; i < 9; ++i) {
		if (possible_number[i] == true) {
			board[x][y] = i + 1;
			sdoku(board, emptyplace, emptyindex + 1);
			board[x][y] = 0;
		}
	}
	return;
}

int main() {
	vector<vector<int>> board(9, vector<int>(9, 0));
	vector<pair<int, int>> emptyplace;
	string str;
	for (int i = 0; i < 9; ++i) {
		cin >> str;
		for (int j = 0; j < 9; ++j) {
			board[i][j] = str[j] - '0';
			if (board[i][j] == 0) emptyplace.push_back(std::make_pair(i, j));
		}
	}

	sdoku(board, emptyplace, 0);
	return 0;
}