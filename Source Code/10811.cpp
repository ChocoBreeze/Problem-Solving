#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	int N, M;
	cin.tie(NULL)->sync_with_stdio(false);
	cin >> N >> M;
	vector<int> vec(N + 1, 0);
	for (int i = 1; i <= N; ++i) vec[i] = i;
	for (int m{}; m < M; ++m) {
		int i, j;
		cin >> i >> j;
		reverse(begin(vec) + i, begin(vec) + j + 1); // [first, last)
	}
	for (int i = 1; i <= N; ++i) cout << vec[i] << ' '; 
	cout << '\n';
	return 0;
}