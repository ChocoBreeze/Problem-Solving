// 2024KB, 0ms
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int K{}; cin >> K;
	string str; cin >> str;
	int strLen{ static_cast<int>(str.length()) };
	vector board(strLen / K, vector<char>(K, 0));
	int x{}, y{};
	for (int s{}, e{ strLen }; s < e;++s) {
		if (s && s % K == 0) {
			++x;
		}
		board[x][y] = str[s];
		if (x & 1) { // --y
			if (y) --y;
		}
		else { // ++y
			if (y < K - 1) ++y;
		}
	}
	
	for (int i{}; i < K;++i) {
		for (int s{}, e{strLen/K}; s < e;++s) {
			cout << board[s][i];
		}
	}
	cout << '\n';

	return 0;
}