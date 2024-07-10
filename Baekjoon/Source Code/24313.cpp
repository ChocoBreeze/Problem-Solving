#include <iostream>

using namespace std;

int main() {

	cin.tie(NULL)->sync_with_stdio(false);	int a1, a0, c, n0;

	cin >> a1 >> a0 >> c >> n0;

	int ans{};

	if (a1 >= c) {

		if (a1 == c && a0 <= 0) ans = 1;

	}

	else { // a1 < c

		double sol = a0 / (c - a1);

		if (sol <= n0) ans = 1;

	}

	cout << ans << '\n';

	return 0;

}