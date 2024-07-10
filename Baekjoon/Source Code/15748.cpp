#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

using pii = pair<int, int>;

int main() {
	cin.tie(NULL)->sync_with_stdio(false);
	int L, N, rf, rb;
	cin >> L >> N >> rf >> rb;
	// L : 거리 | N : stop 개수 | rf, rb : 1m 걸리는 시간

	// 거리 = 시간 * 속력
	vector<pii> vec(N, make_pair(0, 0));
	for (int i = 0; i < N; ++i) {
		cin >> vec[i].first >> vec[i].second; // 위치, 맛
	}
	auto compare = [](const pii& a, const pii& b) {
		return a.second > b.second;
	};
	sort(begin(vec), end(vec), compare);
	// 정렬해서 최대한 많이 먹을 수 있는 곳에서 먹기.

	int now = 0;
	long long answer = 0;
	for (auto& v : vec) {
		if (now < v.first) {
			answer += static_cast<long long>(rf - rb) * (v.first - now) * v.second;
			now = v.first;
		}
	}
	cout << answer << '\n';



	return 0;
}