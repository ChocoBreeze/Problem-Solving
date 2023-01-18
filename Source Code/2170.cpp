// sweeping
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

using pii = pair<int, int>;

int main() {
	cin.tie(NULL)->sync_with_stdio(false);
	int N;
	cin >> N;
	vector<pii> vec(N,make_pair(0,0));
	for (pii& i : vec) {
		cin >> i.first >> i.second;
	}
	auto compare = [](const pii& a, const pii& b) {
		return a.first < b.first;
	};
	sort(begin(vec), end(vec), compare);
	int answer = 0, start = -1000000010, end = -1000000010;
	for (pii& p : vec) {
		if (p.first < end) { // 기존 구간
			end = max(end, p.second);
		}
		else { // 새 구간
			answer += (end - start);
			start = p.first;
			end = p.second;
		}
	}
	answer += (end - start); // 남은 구간 더하기
	cout << answer << '\n';

	return 0;
}