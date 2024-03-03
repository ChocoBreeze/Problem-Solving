// 2020KB, 0ms
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int K{}, N{}, M{}; cin >> K >> N >> M;
	cout << max(0, K * N - M) << '\n';

	return 0;
}