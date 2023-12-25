#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int A, B; cin >> A >> B;
	queue<int> q;
	q.push(B);
	int t{}, reach{};
	while (!q.empty()) {
		int siz = static_cast<int>(size(q));
		for (int i{}; i < siz; ++i) {
			int now = q.front(); q.pop();
			if (now == 0) continue;
			if (now == A) {
				reach = true;
				break;
			}
			if (now % 2 == 0) q.push(now / 2);
			else if (now % 10 == 1) q.push(now / 10);
		}
		++t;
		if (reach) break;
	}
	if (!reach) t = -1;
	cout << t << '\n';

	return 0;
}