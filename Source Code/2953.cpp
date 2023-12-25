#include <iostream>

using namespace std;

int main() {
	int winner{}, winnerScore{-1};
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	for (int i = 1; i <= 5; ++i) {
		int sum{};
		for (int j{}; j < 4; ++j) {
			int s; cin >> s;
			sum += s;
		}
		if (winnerScore < sum) {
			winnerScore = sum;
			winner = i;
		}
	}
	cout << winner << ' ' << winnerScore << '\n';
	return 0;
}