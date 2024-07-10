#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	int T{};
	cin >> T;
	T++;
	string input;
	while (T--) {
		getline(cin, input);
		if (input.empty()) continue;
		istringstream iss(input);
		string temp;
		int sum{};
		while (getline(iss, temp, ' ')) {
			sum += stoi(temp);
		}
		cout << sum << '\n';
	}
	return 0;
}