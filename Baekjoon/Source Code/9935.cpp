#include <iostream>
#include <string>

using namespace std;

int main() {
	cin.tie(NULL)->sync_with_stdio(false);
	string str, bomb, answer("");
	cin >> str >> bomb;
	int index = 0, i;
	answer.resize(str.length());

	for (auto& c : str) {
		answer[index++] = c;
		for (i = 0; i < bomb.length(); ++i) {
			if (index < 1 + i || answer[index - (1 + i)] != bomb[bomb.length() - (1 + i)]) break;
		}
		if (i == bomb.length()) index -= bomb.length();
	}

	if (index > 0) {
		answer.resize(index);
		cout << answer;
	}
	else {
		cout << "FRULA";
	}
	cout << '\n';

	return 0;
}