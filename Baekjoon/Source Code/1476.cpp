#include<iostream>

using std::cin;
using std::cout;

int main() {
	cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	int E, S, M; // 15 28 19
	cin >> E >> S >> M;
	for (int i = 1;; ++i) {
		int E_ = i % 15 == 0 ? 15 : i % 15;
		int S_ = i % 28 == 0 ? 28 : i % 28;
		int M_ = i % 19 == 0 ? 19 : i % 19;
		if (E_ == E && S_ == S && M_ == M) {
			cout << i;
			break;
		}
	}
	return 0;
}