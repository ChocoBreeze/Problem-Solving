#include <iostream>
#include <algorithm>

using namespace std;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int a, b, c, d, e;
	cin >> a >> b >> c >> d >> e;
	int minNum = min({ a,b,c,d,e });

	for (int n{ minNum };; ++n) {
		int cnt{};
		if (n % a == 0) ++cnt;
		if (n % b == 0) ++cnt;
		if (n % c == 0) ++cnt;
		if (n % d == 0) ++cnt;
		if (n % e == 0) ++cnt;
		if (cnt >= 3) {
			cout << n << '\n';
			break;
		}
	}

	return 0;
}