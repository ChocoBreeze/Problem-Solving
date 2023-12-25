#include <iostream>
#include <vector>

using namespace std;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int N{}; cin >> N;

	vector<int> A(N + 1, 0), accum(N + 1, 0);
	for (int n = 1; n <= N; ++n) {
		cin >> A[n];
		accum[n] = accum[n - 1] + A[n];
	}

	int M{}; cin >> M;
	while (M--) {
		int i{}, j{}; cin >> i >> j;
		cout << accum[j] - accum[i - 1] << '\n';
	}

	return 0;
}