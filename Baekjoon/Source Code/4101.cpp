#include <iostream>

using namespace std;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	while (1) {
		int a, b;
		cin >> a >> b;
		if (a == 0 && b == 0) break;
		if (a > b) cout << "Yes\n";
		else cout << "No\n";
	}

	return 0;
}