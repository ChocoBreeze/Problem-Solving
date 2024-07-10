#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main() {
	string str;
	getline(cin, str);
	istringstream iss(str);
	string tmp;
	int cnt{};
	while (getline(iss, tmp, ' ')) {
		if (tmp == "") continue;
		++cnt;
	}

	cout << cnt << endl;
	return 0;
}