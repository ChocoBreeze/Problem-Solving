#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int N{}, M{}; cin >> N;
	int maxCost{};
	vector<int> costs(N, 0);
	for (int& cost : costs) {
		cin >> cost;
		maxCost = max(maxCost, cost);
	}
	cin >> M; // ~ 1'000'000'000
	int answer{};
	int l = 1, r = maxCost; 
	while (l <= r) {
		int mid = l + ((r - l) >> 1); // 상한액

		int sum{};
		for (int& cost : costs) {
			sum += min(mid, cost);
		}

		if (sum <= M) {
			answer = max(mid, answer); // mid는 답이 될 수 있음
			l = mid + 1;
		}
		else r = mid - 1; // mid는 답이 될 수 없음
	}
	cout << answer << '\n';
	return 0;
}