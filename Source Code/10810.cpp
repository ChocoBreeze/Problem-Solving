#include <iostream>
#include <vector>

using namespace std;

int main() {
	int N, M;
	cin.tie(NULL)->sync_with_stdio(false);
	cin >> N >> M;
	vector<int> vec(N + 1, 0);
	for (int m{}; m < M; ++m) {
		int i, j, k;
		cin >> i >> j >> k;
		for (int l{ i }; l <= j; ++l) {
			vec[l] = k;
		}
	}
	for (int i = 1; i <= N; ++i) cout << vec[i] << ' ';
	cout << '\n';

	return 0;
}