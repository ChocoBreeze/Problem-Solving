#include <iostream>

using namespace std;

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);

	int k, q, l, b, n, p;
	cin >> k >> q >> l >> b >> n >> p;
	cout << 1 - k << " " << 1 - q << " " << 2 - l << " " << 2 - b << " " << 2 - n << " " << 8 - p;
	return 0;
}