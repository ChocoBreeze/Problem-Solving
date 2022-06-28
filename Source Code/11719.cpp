#include<iostream>
#include<string>

using namespace std;

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	string str;
	while (getline(cin, str)) {
		if (str.empty()) cout << "\n";
		else cout << str << "\n";
	}
	return 0;
}