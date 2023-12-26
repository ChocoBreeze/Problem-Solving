#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
constinit const int INF = 1 << 30;
// O(TN^2)

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int T{}; cin >> T;
	while (T--) {
		int N{}; cin >> N;
		vector<int> X(N, 0), accum(N + 1, 0);
		for (int n{}; n < N; ++n) {
			cin >> X[n];
			accum[n + 1] = accum[n] + X[n];
		}
		// [i, j] = accum[j] - accum[i - 1]
		int answer{ -INF };
		for (int i{ 1 }; i <= N; ++i) {
			for (int j{ i }; j <= N; ++j) {
				answer = max(answer, accum[j] - accum[i - 1]);
			}
		}
		cout << answer << '\n';
	}
	return 0;
}