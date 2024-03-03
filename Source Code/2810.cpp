// 2024KB, 0ms
#include <iostream>
#include <string>

using namespace std;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int N{}; cin >> N;
	string str; cin >> str;
	int strL = static_cast<int>(str.length());

	int cnt{};
	for (int i{}; i < strL; ++i) {
		if (str[i] == 'S') ++cnt;
		else if (str[i] == 'L') {
			++cnt;
			++i;
		}
	}

	int answer = N < cnt + 1 ? N : cnt + 1;
	cout << answer << '\n';
	return 0;
}