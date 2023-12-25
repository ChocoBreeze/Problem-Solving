#include <iostream>
#include <string>

using namespace std;

int main() {
	while (1) {
		string str;
		getline(cin, str);
		if (str == "#") break; // EOF
		int answer{};
		for (auto& c : str) {
			c |= ' '; // to lower
			if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') ++answer;
		}
		cout << answer << '\n';
	}
	return 0;
}