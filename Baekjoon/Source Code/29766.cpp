#include <iostream>
#include <string>

using namespace std;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	string str;
	cin >> str;

	string DKSH = "DKSH";

	int index = -1, answer{};
	for(;;++answer) {
		index = str.find(DKSH, index + 1);
		if (index == string::npos) break;
	}
	cout << answer << '\n';

	return 0;
}