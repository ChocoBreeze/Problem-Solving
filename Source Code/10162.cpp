#include <iostream>

using namespace std;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int T{}; cin >> T;
	int A{}, B{}, C{};
	A += T / 300, T %= 300;
	B += T / 60, T %= 60;
	C += T / 10, T %= 10;
	if (T) cout << "-1\n";
	else cout << A << ' ' << B << ' ' << C << '\n';
	return 0;
}