#include <iostream>
#include <string>

using namespace std;

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	int M, a, bit = 0;
	string str;
	cin >> M;
	for (int m = 0; m < M; ++m) {
		cin >> str;
		if (str.compare("add") == 0) {
			cin >> a;
			a -= 1;
			bit = bit | (1 << a);
		}
		else if (str.compare("remove") == 0) {
			cin >> a;
			a -= 1;
			bit = bit & ~(1 << a);
		}
		else if (str.compare("check") == 0) {
			cin >> a;
			a -= 1;
			if (bit & (1 << a)) cout << "1\n";
			else cout << "0\n";
		}
		else if (str.compare("toggle") == 0) {
			cin >> a;
			a -= 1;
			bit = bit ^ (1 << a); // xor
		}
		else if (str.compare("all") == 0) {
			bit = (1 << 20) - 1;
		}
		else if (str.compare("empty") == 0) {
			bit = 0;
		}
	}
}