#include <iostream>
#include <string>

using namespace std;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	string a, b; cin >> a >> b;

	for (char& c : a) if (c == '6') c = '5';
	for (char& c : b) if (c == '6') c = '5';
	cout << stoi(a) + stoi(b) << ' ';
	for (char& c : a) if (c == '5') c = '6';
	for (char& c : b) if (c == '5') c = '6';
	cout << stoi(a) + stoi(b) << ' ';

	return 0;
}