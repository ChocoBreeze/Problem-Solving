#include <iostream>

using namespace std;

int main() {
	cin.tie(NULL)->sync_with_stdio(false);
	long long N;
	cin >> N;
	// 1 : 1 ~ n-1 : 2 ~ n
	// n-2 + n-3 + ... 1
	// n-3 + n-4 + ... 1
	// n-4 + ... 1
	// 1
	long long sum{};
	for (long long s{ N - 2 }; s >= 1; --s) {
		sum += s * (s + 1) / 2;
	}
	cout << sum << "\n3\n";

	// 5 + 4 + 3 + 2 + 1 = 15
	// 4 + 3 + 2 + 1 = 10
	// 3 + 2 + 1  = 6
	// 2 + 1 = 3
	// 1 = 1

	return 0;
}