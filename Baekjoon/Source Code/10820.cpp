// 소문자, 대문자, 숫자, 공백의 개수

#include<iostream>
#include<string>

using std::cin;
using std::cout;
using std::string;
using std::getline;

int main() {
	cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	string str;
	while (getline(cin, str)) {
		int lower, upper, number, space;
		lower = upper = number = space = 0;
		for (auto& s : str) {
			if ('A' <= s && s <= 'Z') ++upper;
			else if ('a' <= s && s <= 'z') ++lower;
			else if ('0' <= s && s <= '9') ++number;
			else if (s == ' ') ++space;
		}
		cout << lower << " " << upper << " " << number << " " << space << "\n";
	}

	return 0;
}