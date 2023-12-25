#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int N{}, K{}; cin >> N >> K;
	vector<int> vecs(N, 0);
	vector<long long> accum(N, 0);
	cin >> vecs[0];
	accum[0] = vecs[0];
	for (int n = 1; n < N; ++n) {
		cin >> vecs[n];
		accum[n] = vecs[n] + accum[n - 1];
	}

	sort(begin(accum), end(accum), greater<long long>());
	long long answer{};
	for (int k{}; k < K; ++k) {
		answer += accum[k];
	}
	cout << answer << '\n';

	return 0;
}
