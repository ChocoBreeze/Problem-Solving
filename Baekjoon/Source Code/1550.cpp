#include <iostream>
#include <string>

using namespace std;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	string str;
	cin >> str;
	int sum{};
	for (auto it = begin(str); it != end(str); ++it) {
		sum *= 16;
		if (*it >= '0' && *it <= '9') sum += *it - '0';
		else sum += *it - 'A' + 10;
	}
	cout << sum << '\n';

	return 0;
}