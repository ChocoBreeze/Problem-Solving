#include <iostream>
#include <queue>

using namespace std;

bool check(int p, int q,int s,int b) {
	int p1 = p / 100, p2 = p / 10 % 10, p3 = p % 10;
	int q1 = q / 100, q2 = q / 10 % 10, q3 = q % 10;

	int strike = 0 ,ball = 0;
	if (p1 == q1) strike++;
	if (p2 == q2) strike++;
	if (p3 == q3) strike++;

	if (p1 == q2 || p1 == q3) ball++;
	if (p2 == q1 || p2 == q3) ball++;
	if (p3 == q1 || p3 == q2) ball++;

	if (strike == s && ball == b) return true;
	else return false;
}

int main() {
	cin.tie(NULL)->sync_with_stdio(false);
	// 9*8*7 = 504

	vector<int> possibles;
	possibles.reserve(520);
	for (int i = 1; i <= 9; ++i) {
		for (int j = 1; j <= 9; ++j) {
			if (i == j) continue;
			for (int k = 1; k <= 9; ++k) {
				if (k == i || k == j) continue;
				int num = 100 * i + 10 * j + k;
				possibles.push_back(num);
			}
		}
	}

	vector<int> chk(504, 1);
	int N, num, s, b;
	cin >> N;
	for (int i = 0; i < N; ++i) {
		cin >> num >> s >> b;
		for (int j = 0; j < possibles.size();++j) {
			if (!check(possibles[j], num, s, b)) chk[j] = 0;
		}
	}

	int answer = 0;
	for (int& i : chk) {
		if (i) ++answer;
	}
	cout << answer << '\n';
	return 0;
}