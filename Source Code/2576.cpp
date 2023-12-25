#include <iostream>
#include <algorithm>

using namespace std;
constinit const int MAXNUM = 1010;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int sum{}, minNum{ MAXNUM };
	for (int i{}; i < 7; ++i) {
		int num{}; cin >> num;
		if (num & 1) {
			sum += num;
			minNum = min(minNum, num);
		}
	}
	if (minNum == MAXNUM) cout << "-1\n";
	else cout << sum << '\n' << minNum << '\n';

	return 0;
}