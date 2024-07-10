#include <iostream>
#include <cmath>

using namespace std;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int L{}; cin >> L;
	cout << fixed;
	cout.precision(10);
	const double SIN120 = sqrt(3) * 0.5;
	cout << 0.5 * L * L * SIN120 << '\n';
	return 0;
}