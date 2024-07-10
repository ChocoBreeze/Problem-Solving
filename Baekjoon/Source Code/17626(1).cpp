// https://www.acmicpc.net/board/view/125519
// BruteForce도 되네 => 223 * 223 * 223 = 11'089'567
// 2020KB, 12ms
#include <iostream>
#include <algorithm>

using namespace std;
constinit const int LAST = 224;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int n{}; cin >> n;
	int answer{ 4 };
	for (int i{}; i < LAST; ++i) {
		for (int j{}; j < LAST; ++j) {
			for (int k{}; k < LAST; ++k) {
				if (i * i + j * j + k * k == n) {
					int cnt{};
					if (i) ++cnt;
					if (j) ++cnt;
					if (k) ++cnt;
					answer = min(answer, cnt);
				}
			}
		}
	}
	cout << answer << '\n';

	return 0;
}