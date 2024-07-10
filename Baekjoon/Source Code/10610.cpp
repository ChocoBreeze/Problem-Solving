#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	string s; cin >> s;
	bool divideByTen{};
	int sum{}; // 자리수 합
	for (char& c : s) {
		if (c == '0') divideByTen = true;
		sum += c - '0';
	}
	// 30의 배수
	// 10으로 나눠떨어지고, 3으로 나눠떨어지고
	string answer("-1");
	if (sum % 3 == 0 && divideByTen) {
		sort(begin(s), end(s), greater<>());
		answer.swap(s);
	}
	cout << answer << '\n';

	return 0;
}