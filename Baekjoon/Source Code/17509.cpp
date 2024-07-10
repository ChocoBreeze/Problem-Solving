#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

using pii = pair<int, int>;

int main() {
	cin.tie(NULL)->sync_with_stdio(false);
	vector<pair<int, int>> vec(11, make_pair(0, 0));
	for (int i = 0; i < 11; ++i) {
		cin >> vec[i].first >> vec[i].second;
	}
	auto compare = [](const pii& a, const pii& b) {
		return a.first < b.first;
	};
	sort(begin(vec), end(vec), compare);

	int answer = 0;
	int t = 0;
	for (pii& v : vec) {
		t += v.first;
		answer += t + 20 * v.second;
	}

	cout << answer;

	return 0;
}