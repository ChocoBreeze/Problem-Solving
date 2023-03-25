#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int main() {
	cin.tie(NULL)->sync_with_stdio(false);
	string scroll;
	cin >> scroll;

	string devils, angels;
	cin >> devils >> angels;
	int stoneLength = static_cast<int>(devils.length());
	int scrollLength = static_cast<int>(scroll.length());

	vector<vector<int>> DP(2, vector<int>(scrollLength, 0));

	for (int i = 0; i < stoneLength; ++i) {
		vector<vector<int>> tempDP(begin(DP), end(DP));
		for (int j = 0; j < scrollLength; ++j) {
			if (devils[i] == scroll[j]) {
				if (j == 0) {
					tempDP[0][j]++;
				}
				else {
					if (DP[1][j - 1] > 0) {
						tempDP[0][j] += DP[1][j - 1];
					}
				}
			}
			if (angels[i] == scroll[j]) {
				if (j == 0) {
					tempDP[1][j]++;
				}
				else {
					if (DP[0][j - 1] > 0) {
						tempDP[1][j] += DP[0][j - 1];
					}
				}
			}
		}
		DP = move(tempDP);
	}
	cout << DP[0][scrollLength - 1] + DP[1][scrollLength - 1] << '\n';
	return 0;
}