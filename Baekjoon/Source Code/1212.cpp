#include <iostream>
#include <string>

// oct -> bin

using namespace std;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	string str; cin >> str;

	string answer;
	for (auto it = begin(str); it != end(str); ++it) {
		if (*it == '0') {
			if (!answer.empty()) answer += "000"s;
		}
		else if (*it == '1') {
			if (answer.empty()) answer.push_back('1');
			else answer += "001"s;
		}
		else if (*it == '2') {
			if (answer.empty()) answer += "10"s;
			else answer += "010"s;
		}
		else if (*it == '3') {
			if (answer.empty()) answer += "11"s;
			else answer += "011"s;
		}
		else if (*it == '4') answer += "100"s;
		else if (*it == '5') answer += "101"s;
		else if (*it == '6') answer += "110"s;
		else if (*it == '7') answer += "111"s;
	}
	if (answer.empty()) cout << "0\n";
	else cout << answer << '\n';

	return 0;
}