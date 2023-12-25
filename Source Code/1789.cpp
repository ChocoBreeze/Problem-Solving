#include <iostream>

using namespace std;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	long long S{}; cin >> S;
	S <<= 1;
	
	for (long long i{};; ++i) {
		if (i * i + i > S) {
			cout << i - 1 << '\n';
			break;
		}
	}

	return 0;
}