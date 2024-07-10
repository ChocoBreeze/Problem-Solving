#include<iostream>
#include<string>

using std::cin;
using std::cout;
using std::string;

int main() {
	cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	string str;
	int cnt_change = 0;
	cin >> str;
	for (int i = 0; i < str.length()-1; ++i) {
		if (str[i] != str[i + 1]) ++cnt_change;
	}
	if (cnt_change % 2 == 0) cout << cnt_change / 2;
	else cout << cnt_change / 2 + 1;
	return 0;
}