#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

using pii = pair<int, int>;

int main() {
	cin.tie(NULL)->sync_with_stdio(false);
	int N;
	cin >> N;
	vector<pii> vec(N, make_pair(0, 0));
	for (auto& n : vec) {
		cin >> n.first >> n.second;
	}
	auto compare = [](const pii& a, const pii& b) {
		if (a.second == b.second) return a.first < b.first;
		return a.second < b.second;
	};
	sort(begin(vec), end(vec), compare);

	int last_time = 0, answer = 0;
	for (auto& v : vec) {
		if (last_time <= v.first) {
			last_time = v.second;
			answer++;
		}
	}
	cout << answer << '\n';


	return 0;
}