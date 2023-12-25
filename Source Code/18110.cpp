/*
* 상위 15%, 하위 15% 제외 => 제외 인원은 반올림해서 결정
* 계산된 점수도 정수로 반올림.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int n; cin >> n;
	vector<int> scores(n, 0);
	for (int& s : scores) cin >> s;
	sort(begin(scores), end(scores));

	int cuttingPeople = static_cast<int>(static_cast<double>(n) * 15 / 100 + 0.5);

	int sum{};
	for (int i{ cuttingPeople }; i < n - cuttingPeople; ++i) {
		sum += scores[i];
	}

	int answer{};
	if (n) answer = static_cast<int>(static_cast<double>(sum) / (n - 2 * cuttingPeople) + 0.5);
	cout << answer << '\n';

	return 0;
}