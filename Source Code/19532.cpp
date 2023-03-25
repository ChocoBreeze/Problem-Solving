// 각 칸에는 -999 이상 999 이하의 정수만 입력할 수 있음.

#include <iostream>

using namespace std;

int main() {
	cin.tie(NULL)->sync_with_stdio(false);
	int a, b, c, d, e, f;
	cin >> a >> b >> c >> d >> e >> f;

	// 2000 * 2000 = 4000000
	[&]() {
		for (int x{ -999 }; x <= 999; ++x) {
			for (int y{ -999 }; y <= 999; ++y) {
				if (a * x + b * y == c && d * x + e * y == f) {
					cout << x << ' ' << y << '\n';
					return 0;
				}
			}
		}
	} ();

	return 0;
}