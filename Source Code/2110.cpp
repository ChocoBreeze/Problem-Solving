#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	cin.tie(NULL)->sync_with_stdio(false);
	int N, C;
	cin >> N >> C;
	vector<int> wifi(N, 0);
	for (auto& w : wifi) cin >> w;
	sort(begin(wifi), end(wifi));
	int start = 1, end = wifi.back() - wifi.front() + 1; // end 범위를 잘 확인하자! (75% 통과 못한 이유)
	while (start < end) {
		int mid = start + (end - start) / 2; // 만들 수 있는 간격
		int cnt = 0, last_choice = wifi[0];
		for (int i = 1; i < N; ++i) {
			if (wifi[i] - last_choice >= mid) {
				last_choice = wifi[i];
				++cnt;
			}
		}
		if (cnt < C - 1) end = mid;
		else start = mid + 1;
	}
	cout << start - 1;
	return 0;
}