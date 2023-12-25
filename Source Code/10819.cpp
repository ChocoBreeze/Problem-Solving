#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int N{}; cin >> N;
	vector<int> A(N, 0);
	for (int& a : A) cin >> a;

	sort(begin(A), end(A));
	int answer{};

	do {
		int sum{};
		for (int n{}; n < N - 1; ++n) {
			int absV{};
			if (A[n] < A[n + 1]) absV = A[n + 1] - A[n];
			else absV = A[n] - A[n + 1];
			sum += absV;
		}
		answer = max(answer, sum);
	} while (next_permutation(begin(A), end(A)));
	cout << answer << '\n';

	return 0;
}