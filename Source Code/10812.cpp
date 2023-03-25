#include <iostream>
#include <vector>

using namespace std;

int main() {
	int N, M;
	cin.tie(NULL)->sync_with_stdio(false);
	cin >> N >> M;
	vector<int> vec(N + 1, 0);
	for (int i = 0; i <= N; ++i) vec[i] = i;
	for (int m{}; m < M; ++m) {
		int i, j, k;
		cin >> i >> j >> k;

		vector<int> tmp(vec.begin() + i, vec.begin() + j + 1);
		int len = static_cast<int>(tmp.size());
		for (int t = 0; t < len; ++t) {
			vec[i + t] = tmp[(t + k - i) % len];
		}

	}

	// 1 2 3 4 5 6 7 8 9 10
	// 4 5 6 1 2 3 7 8 9 10
	// 4 5 8 9 6 1 2 3 7 10
	for (int i = 1; i <= N; ++i) cout << vec[i] << ' ';
	cout << '\n';

	return 0;
}