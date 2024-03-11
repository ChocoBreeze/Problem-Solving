// 2024KB, 0ms
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;
void AddRev(string& s, string& ss) {
	for (auto it{ rbegin(ss) }; it != rend(ss); ++it) {
		s.push_back(*it);
	}
}

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	string str; cin >> str;
	string answer;
	for (int i{}; i < 51; ++i) answer.push_back('z');

	int strLen = static_cast<int>(str.length());
	for (int i{ 1 }; i < strLen; ++i) {
		// [0, i) + [i, j) + [j, )
		for (int j{ i + 1 }; j < strLen; ++j) {
			string a = str.substr(0, i);
			string b = str.substr(i, j - i);
			string c = str.substr(j);

			string ret;
			AddRev(ret, a);
			AddRev(ret, b);
			AddRev(ret, c);
			answer = min(answer, ret);
		}
	}
	cout << answer << '\n';

	return 0;
}