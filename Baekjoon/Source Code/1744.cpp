#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int N; cin >> N;
	vector<int> nums(N, 0);
	for (int& n : nums) cin >> n;
	sort(begin(nums), end(nums));

	int answer{};
	bool positive{};
	for (int n{}; n < N; ++n) {
		if (!positive && nums[n] > 1) positive = true;
		if (positive) {
			if ((N-n) & 1) answer += nums[n];
			else {
				// answer += nums[n] * nums[++n];
				answer += nums[n] * nums[n + 1];
				++n;
			}
		}
		else {
			if (n + 1 < N) {
				if (nums[n + 1] <= 0) {
					answer += nums[n] * nums[n + 1];
					++n;
				}
				else answer += nums[n];
			}
			else answer += nums[n];
		}
	}
	cout << answer << '\n';

	return 0;
}