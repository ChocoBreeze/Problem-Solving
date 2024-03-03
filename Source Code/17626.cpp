/*
1 => 223개 (223 * 223 = 49729)
1 + 1 => 223 * 223 : 49'729개
1 + 2 => 223 * 223 * 223 : 11'089'567개
*/
// 2412KB, 4ms
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
constinit const int SIZE = 50001;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int n{}; cin >> n;
	vector<int> dat(SIZE, 4), one, two;
	one.reserve(230); // 223 * 223 = 49729
	for (int i{ 1 }; i * i < SIZE; ++i) { // 제곱수 하나로 구성
		dat[i * i] = 1;
		one.push_back(i * i);
		if (i * i == n) {
			cout << "1\n";
			return 0;
		}
	}
	two.reserve(49740);
	for (int i{}; i < static_cast<int>(one.size()); ++i) {
		for (int j{}; j < static_cast<int>(one.size()); ++j) {
			int num = one[i] + one[j];
			if (num >= SIZE || dat[num] <= 2) continue;
			dat[num] = 2;
			two.push_back(num);
			if (num == n) {
				cout << "2\n";
				return 0;
			}
		}
	}
	for (int i{}; i < static_cast<int>(one.size()); ++i) {
		for (int j{}; j < static_cast<int>(two.size()); ++j) {
			int num = one[i] + two[j];
			if (num >= SIZE || dat[num] <= 3) continue;
			dat[num] = 3;
			if (num == n) {
				cout << "3\n";
				return 0;
			}
		}
	}
	cout << "4\n";
	return 0;
}