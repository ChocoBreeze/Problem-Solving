#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	int N, k;
	cin >> N >> k;
	vector<int> s(N, 0);
	for (auto& i : s) {
		cin >> i;
	}
	sort(begin(s), end(s), greater<int>());
	cout << *(begin(s) + (k - 1));
	return 0;
}