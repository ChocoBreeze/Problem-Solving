#include <iostream>
#include <vector>

using namespace std;
using ll = long long;
constexpr int SIZE = 1'000'010;

int main() {
	cin.tie(NULL)->sync_with_stdio(false);
	int T;
	cin >> T;

	vector<int> primes(SIZE, 1);
	primes[0] = primes[1] = 0;
	for (int i{ 2 }; i < SIZE; ++i) {
		if (primes[i]) {
			for (ll j = i + i; j < SIZE; j += i) {
				primes[j] = 0;
			}
		}
	}

	for (int t{}; t < T; ++t) {
		int N;
		cin >> N;
		int cnt{};

		for (int i = 2; i <= N / 2; ++i) {
			if (primes[i] && primes[N - i]) {
				// 두 소수의 순서만 다른 것은 같은 파티션
				++cnt;
			}
		}
		cout << cnt << '\n';
	}

	return 0;
}