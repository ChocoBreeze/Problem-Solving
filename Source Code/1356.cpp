#include <iostream>
#include <string>

using namespace std;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	string str;
	cin >> str;
	int mul{ 1 };
	for (auto& c : str) mul *= c - '0';

	bool chk{};
	for (int i{}; i < static_cast<int>(str.length()) - 1;++i) {
		// 101
		int firstHalf{ 1 }, secondHalf{ 1 };
		for (int j{}; j < static_cast<int>(str.length()); ++j) {
			if (j <= i) firstHalf *= str[j] - '0';
			else secondHalf *= str[j] - '0';
		}
		if (firstHalf == secondHalf) {
			chk = true;
			break;
		}
	}
	if (chk) cout << "YES\n";
	else cout << "NO\n";

	return 0;
}