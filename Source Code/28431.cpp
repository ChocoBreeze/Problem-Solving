#include <iostream>
#include <vector>

using namespace std;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	vector<int> count(10, 0);
	for (int i{}; i < 5; ++i) {
		int n{}; cin >> n;
		count[n]++;
	}
	int answer{};
	for (int i{}; i < 10; ++i) {
		if (count[i] & 1) answer = i;
	}
	cout << answer << '\n';
	return 0;
}