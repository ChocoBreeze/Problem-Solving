#include <iostream>
#include <string>

using namespace std;

int main() {
	cin.tie(NULL)->sync_with_stdio(false);
	string n;
	while (1) {
		cin >> n;
		if (!n.compare("0")) break;
		int times = n.length() / 2;
		bool is_palindrome = true;
		for (int i = 0; i < times; ++i) {
			if (n[i] != n[n.length() - i - 1]) {
				is_palindrome = false;
				break;
			}
		}
		if (is_palindrome) cout << "yes\n";
		else cout << "no\n";
	}
	
	return 0;
}