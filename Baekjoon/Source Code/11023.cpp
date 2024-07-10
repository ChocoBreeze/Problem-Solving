#include <iostream>
#include <string>

using namespace std;

int main() {
	int a{}, sum{};
	while (1) {
		cin >> a;
		if (cin.eof()) break;
		sum += a;
	}
	cout << sum << '\n';
	return 0;
}