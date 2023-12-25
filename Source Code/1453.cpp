#include <iostream>

using namespace std;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int N{}; cin >> N;
	int used[101]{};
	int cnt{};
	while (N--) {
		int in; cin >> in;
		if (used[in]) ++cnt;
		else used[in] = 1;
	}
	cout << cnt << '\n';

	return 0;
}