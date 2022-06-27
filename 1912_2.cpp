#include<iostream>
#include<vector>
#include<algorithm>

using std::cin;
using std::cout;
using std::vector;
using std::max;

int main() {
	cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	int N;
	cin >> N;
	vector<int> A(N, 0);
	for (int i = 0; i < N; ++i) {
		cin >> A[i];
	}
	int max_end = -1001, max_seen = -1001;
	for (auto& i : A) {
		max_end = max(i, i + max_end);
		max_seen = max(max_seen, max_end);
	}
	std::cout << max_seen;
	return 0;
}