// 참고.
// https://www.acmicpc.net/source/57188860
#include <iostream>
#include <vector>
#include <algorithm>

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

		auto beg = begin(vec);
		reverse(beg + i, beg + j + 1);
		reverse(beg + i, beg + (i + j - k + 1));
		reverse(beg + (i + j - k + 1), beg + j + 1);
	}

	// 1 2 3 4 5 6 7 8 9 10
	// 6 5 4 3 2 1 7 8 9 10
	// 4 5 6 3 2 1 7 8 9 10
	
	for (int i = 1; i <= N; ++i) cout << vec[i] << ' ';
	cout << '\n';

	return 0;
}