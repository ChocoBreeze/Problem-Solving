#include <iostream>

using namespace std;

int main() {
	int T, C;
	cin >> T;
	while (T--) {
		cin >> C;
		cout << C / 25 << ' ' << C % 25 / 10 << ' '
			<< C % 25 % 10 / 5 << ' ' << C % 25 % 10 % 5 << '\n';
	}
	return 0;
}