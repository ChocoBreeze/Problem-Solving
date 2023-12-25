#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>

using namespace std;
using pii = pair<int, int>;
constinit const int INF = 1 << 30;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int T{}; cin >> T; // ~ 20
	while (T--) {
		int N{}; cin >> N; // ~ 100'000
		// (index, 등수)
		vector<pii> score(N, make_pair(0, 0));
		for (auto& s : score) {
			cin >> s.first >> s.second; // 서류, 면접
		}
		// 서류 점수를 우선시해서 오름차순 정렬
		sort(begin(score), end(score));

		int lastMeet{ INF }, answer{};
		for (auto& s: score) {
			if (lastMeet > s.second) { // 이 때까지 나온 사람들의 면접 등수보다 더 낮은 경우에만 선발 가능함!
				++answer;
				lastMeet = s.second; // 서류 점수가 높은 사람의 면접 등수 반영
			}
		}
		
		cout << answer << '\n';
	}

	return 0;
}