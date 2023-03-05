#include <iostream>
#include <queue>

using namespace std;

const int MAX_N = 1001;

int main() {
	cin.tie(NULL)->sync_with_stdio(false);
	int N;
	cin >> N;

	vector<priority_queue<int>> Q(MAX_N); // max_heap
	// 뒤에서부터 보면 어떨까?

	int d, w, max_day;
	for (int i = 0; i < N; ++i) {
		cin >> d >> w;
		Q[d].push(w);
	}

	int ans = 0, max, day;
	for (int i = MAX_N - 1; i >= 1; --i) {
		max = -1, day = 0;
		for (int j = i; j <= MAX_N - 1; ++j) {
			if (Q[j].empty()) continue;
			if (max < Q[j].top()) {
				max = Q[j].top();
				day = j;
			}
		}
		if (day) {
			ans += max;
			Q[day].pop();
		}
	}
	cout << ans << '\n';

	return 0;
}