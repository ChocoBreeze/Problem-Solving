#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int N; cin >> N;
	vector<int> xs(N, 0);
	for (int& x : xs) cin >> x;
	sort(begin(xs), end(xs)); // 오름차순

	int group{}, index{};
	while(index < N) {
		index += xs[index];
		++group;
	}

	cout << group << '\n';
	return 0;
}