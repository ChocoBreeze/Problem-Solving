#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int n{}; cin >> n;
	for (int i{ 1 };i<=n;++i) {
		vector<int> len(3, 0);
		for (int& l : len) cin >> l;
		sort(begin(len), end(len));
		cout << "Scenario #" << i << ":\n";
		if (len[2] * len[2] == (len[0] * len[0] + len[1] * len[1])) cout << "yes\n";
		else cout << "no\n";
		cout << '\n';
	}
	return 0;
}