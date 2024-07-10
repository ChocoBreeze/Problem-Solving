#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int main() {
	string str;
	cin.tie(NULL)->sync_with_stdio(false);
	cin >> str;
	string reversestr = str;
	reverse(begin(reversestr), end(reversestr));
	if (str == reversestr) cout << "1\n";
	else cout << "0\n";

	return 0;
}