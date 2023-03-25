#include <iostream>
#include <string>

using namespace std;

int main() {
	int i;
	string str;
	cin.tie(NULL)->sync_with_stdio(false);
	cin >> str >> i;
	
	cout << str[i - 1] << '\n';
	return 0;
}