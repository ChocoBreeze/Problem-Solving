#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int N{}; cin >> N;
	int answer = -1;
	for (int n{}; n < N; ++n) {
		int run1{}, run2{};
		cin >> run1 >> run2;

		vector<int> tricks(5, 0);
		for (int& t : tricks) cin >> t;
		sort(begin(tricks), end(tricks));

		int score = max(run1, run2) + tricks[3] + tricks[4];
		answer = max(answer, score);
	}
	cout << answer << '\n';
	return 0;
}