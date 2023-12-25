#include <iostream>

using namespace std;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int N{}, F{}; cin >> N >> F;

	N /= 100;
	N *= 100;

	for (int n{}; n < 100; ++n) {
		if ((N + n) % F == 0) {
			if (n < 10) {
				cout << '0' << n << '\n';
			}
			else cout << n << '\n';
			break;
		}
	}
	
	return 0;
}