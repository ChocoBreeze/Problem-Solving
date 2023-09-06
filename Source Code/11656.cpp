#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	cin.tie(nullptr), ios::sync_with_stdio(false);

	string str; cin >> str;
	int len = static_cast<int>(str.length());

	vector<string> answer;
	for (int l{}; l < len; ++l) {
		string subStr = str.substr(static_cast<size_t>(len - 1 - l));
		answer.push_back(subStr);
	}

	sort(begin(answer), end(answer));
	for (string& a : answer) cout << a << '\n';

	return 0;
}