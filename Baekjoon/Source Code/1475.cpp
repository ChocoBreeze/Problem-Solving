// 2024KB, 0ms
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	string N{}; cin >> N;
	vector<int> DAT(9, 0); // 0 ~ 8
	for (auto& c : N) {
		if (c == '9') DAT[6]++;
		else {
			DAT[c - '0']++;
		}
	}
	int answer{};
	for (int i{}; i < 9;++i) {
		if (i == 6) answer = max(answer, DAT[i] / 2 + (DAT[i] & 1 ? 1 : 0));
		else answer = max(answer, DAT[i]);
	}
	cout << answer << '\n';

	return 0;
}