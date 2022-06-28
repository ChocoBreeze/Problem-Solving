#include<iostream>
using std::cin;
using std::cout;
int main() {
	cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	int T, a, b, last;
	cin >> T;
	for (int i = 0; i < T; ++i) {
		cin >> a >> b;
		last = a;
		for (int j = 1; j < b; ++j) {
			last *= a;
			last %= 10;
		}
		if (last % 10 == 0) cout << "10\n";
		else cout << last % 10 << "\n";
	}
	return 0;
}