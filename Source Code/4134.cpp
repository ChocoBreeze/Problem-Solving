// root(4'000'000'000) = 63245...
// test case가 널널한가?
#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

int main() {
	cin.tie(NULL)->sync_with_stdio(false);
	
	// 그냥 간단하게 확인해라
	int T;
	cin >> T;
	for (int t{}; t < T; ++t) {
		ll n;
		cin >> n;
		if (n == 0 || n == 1) {
			cout << 2 << '\n';
			continue;
		}

		for (;; ++n) {
			bool chk{ true };
			for (ll j = 2; j*j <= n; ++j) {
				if (n%j == 0) {
					chk = false;
					break;
				}
			}
			if (chk) {
				cout << n << '\n';
				break;
			}
		}
	}


	return 0;
}