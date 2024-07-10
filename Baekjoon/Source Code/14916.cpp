#include <iostream>

using namespace std;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int n{}; cin >> n;

	if (!((n % 5) & 1)) { // 5로 나눈 나머지가 짝수
		cout << (n / 5) + (n % 5) / 2 << '\n';
	}
	else { //
		if (n > 5) {
			cout << (n / 5) - 1 + ((n % 5) + 5) / 2 << '\n';
		}
		else {
			if (n % 2 == 0) cout << n / 2 << '\n';
			else cout << "-1\n";
		}

	}

	return 0;
}