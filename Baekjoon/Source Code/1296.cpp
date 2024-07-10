#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	string yeondu;
	cin >> yeondu;
	int iL{}, iO{}, iV{}, iE{};
	for (auto& c : yeondu) {
		if (c == 'L') iL++;
		if (c == 'O') iO++;
		if (c == 'V') iV++;
		if (c == 'E') iE++;
	}
	int N{}, maxScore = -1;
	cin >> N;
	string answer;
	for (int n{}; n < N; ++n) {
		string team; cin >> team;
		int L{iL}, O{iO}, V{iV}, E{iE};
		for (auto& c : team) {
			if (c == 'L') L++;
			if (c == 'O') O++;
			if (c == 'V') V++;
			if (c == 'E') E++;
		}
		int score = ((((L + O) * (L + V)) % 100 * (L + E) * (O + V)) % 100 * (O + E) * (V + E)) % 100;
		if (score > maxScore) {
			maxScore = score;
			answer = team;
		}
		else if (score == maxScore) {
			if (answer > team) answer = team;
		}
	}

	cout << answer << '\n';

	return 0;
}