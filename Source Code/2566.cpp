#include <iostream>

using namespace std;

int main() {
	cin.tie(NULL)->sync_with_stdio(false);
	int ans_x = 0, ans_y = 0, max = -1, tmp;

	for (int i = 1; i < 10; ++i) {
		for (int j = 1; j < 10; ++j) {
			cin >> tmp;
			if (max < tmp) {
				max = tmp;
				ans_x = i;
				ans_y = j;
			}
		}
	}
	cout << max << '\n' << ans_x << " " << ans_y;

	return 0;
}