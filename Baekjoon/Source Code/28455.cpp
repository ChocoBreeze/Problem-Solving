// 입력 안 받고 정렬하고 있네 ㅋㅋ
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int N; cin >> N;

	vector<int> levels(N, 0);
	for (int& l : levels) cin >> l;
	sort(begin(levels), end(levels), greater<int>());
	int levelSum{}, statSum{};

	for (int n{}; n < min(N,42); ++n) {
		int& L = levels[n];
		levelSum += L;
		if (L >= 60) statSum++;
		if (L >= 100) statSum++;
		if (L >= 140) statSum++;
		if (L >= 200) statSum++;
		if (L >= 250) statSum++;
	}
	cout << levelSum << ' ' << statSum << '\n';
	return 0;
}