#include<iostream>
#include<vector>
#include<string>
using std::vector;
using std::cin;
using std::cout;
using std::string;

int cal_case1(vector<string>& board, int i, int j) { // B
	int count = 0;
	for (int m = i; m < i + 8; m += 2) {
		for (int n = j; n < j + 8; n += 2) {
			if (board[m][n] != 'B') count++;
			if (board[m][n + 1] != 'W') count++;
			if (board[m + 1][n] != 'W') count++;
			if (board[m + 1][n + 1] != 'B') count++;
		}
	}
	return count;
}

int cal_case2(vector<string>& board, int i, int j) { // W
	int count = 0;
	for (int m = i; m < i + 8; m += 2) {
		for (int n = j; n < j + 8; n += 2) {
			if (board[m][n] != 'W') count++;
			if (board[m][n + 1] != 'B') count++;
			if (board[m + 1][n] != 'B') count++;
			if (board[m + 1][n + 1] != 'W') count++;
		}
	}
	return count;
}

int main() {
	int N, M;
	string input;
	vector<string> board;
	cin >> N >> M;
	for (int i = 0; i < N; ++i) {
		cin >> input;
		board.push_back(input);
	}
	int answer = 64, count1, count2;
	for (int i = 0; i < N - 7; ++i) {
		for (int j = 0; j < M - 7; ++j) {	
			count1 = cal_case1(board, i, j);
			count2 = cal_case2(board, i, j);
			if (answer > count1) answer = count1;
			if (answer > count2) answer = count2;
		}
	}
	cout << answer;
	return 0;
}