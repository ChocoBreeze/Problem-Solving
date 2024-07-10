#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int T; cin >> T;
	for (int t{}; t < T; ++t) {
		string str, temp;
		getline(cin, str);
		if (str == "") {
			t--;
			continue;
		}
		istringstream iss(str);
		while (getline(iss, temp, ' ')) {
			for (auto it = rbegin(temp); it != rend(temp); ++it) {
				cout << *it;
			}
			cout << ' ';
		}
		cout << '\n';
	}

	return 0;
}