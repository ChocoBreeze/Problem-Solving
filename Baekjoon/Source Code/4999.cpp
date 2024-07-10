// 2024KB, 0ms
#include <iostream>
#include <string>

using namespace std;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	string a, b;
	cin >> a >> b;

	if (a.length() < b.length()) cout << "no\n";
	else cout << "go\n";

	return 0;
}