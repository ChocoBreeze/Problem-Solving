// 2020KB, 0ms
#include <iostream>

using namespace std;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	while (1) {
		int n{}; cin >> n;
		if (n == 0) break;
		cout << n * (n + 1) / 2 << '\n';
	}
	return 0;
}