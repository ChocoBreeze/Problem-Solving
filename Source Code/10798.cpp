#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	cin.tie(NULL)->sync_with_stdio(false);
	vector<string> strs(5, "");
	int maxLen{ -1 };
	for (string& str : strs) {
		cin >> str;
		maxLen = max(maxLen, static_cast<int>(str.length()));
	}
	for (int i = 0; i < maxLen; ++i) {
		for (int j = 0; j < 5; ++j) {
			if (strs[j].length() <= i) continue;
			cout << strs[j][i];
		}
	}
	cout << '\n';


	return 0;
}