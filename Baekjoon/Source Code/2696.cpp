#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main() {
	int T{};
	cin.tie(NULL)->sync_with_stdio(false);
	cin >> T;

	for (int t = 0; t < T; ++t) {
		int M{}, value{};
		cin >> M;
		vector<int> ans;
		ans.reserve(M);
		priority_queue<int, vector<int>, greater<int>> minH;
		priority_queue<int> maxH;
		// 중간값 = maxH.top()
		for (int m = 0; m < M; ++m) {
			cin >> value;
			if (maxH.size() == minH.size()) maxH.push(value);
			else minH.push(value);
			if (!maxH.empty() && !minH.empty() && maxH.top() > minH.top()) {
				int maxHtop = maxH.top(); maxH.pop();
				int minHtop = minH.top(); minH.pop();
				maxH.push(minHtop); minH.push(maxHtop);
			}
			if (m % 2 == 0) ans.push_back(maxH.top());
		}

		cout << ans.size() << '\n';
		for (int i = 0; i < ans.size(); ++i) {
			cout << ans[i] << ' ';
			if ((i + 1) % 10 == 0) cout << '\n';
		}
		if (ans.size() % 10 != 0) cout << '\n';
		
	}

	return 0;
}