// 3680KB, 20ms
#include <iostream>
#include <string>

using namespace std;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int N{}; cin >> N;
	string str; cin >> str;

	while (static_cast<int>(str.length()) != 1) {
		char first = str.back(); str.pop_back();
		char second = str.back(); str.pop_back();
		if (first == second) str.push_back(first); // AA, GG, CC, TT
		else if (first == 'A') {
			if (second == 'G') str.push_back('C');
			else if (second == 'C') str.push_back('A');
			else if (second == 'T') str.push_back('G');
		}
		else if (first == 'G') {
			if (second == 'A') str.push_back('C');
			else if (second == 'C') str.push_back('T');
			else if (second == 'T') str.push_back('A');
		}
		else if (first == 'C') {
			if (second == 'A') str.push_back('A');
			else if (second == 'G') str.push_back('T');
			else if (second == 'T') str.push_back('G');
		}
		else if (first == 'T') {
			if (second == 'A') str.push_back('G');
			else if (second == 'G') str.push_back('A');
			else if (second == 'C') str.push_back('G');
		}
	}
	cout << str << '\n';
	return 0;
}