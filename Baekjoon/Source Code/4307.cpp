#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	int T, l, as;
	cin >> T;
	for (int t = 0; t < T; ++t) {
		cin >> l >> as;
		int mini = -1, maxi = -1, p;
		for (int a = 0; a < as; ++a) {
			cin >> p;
			int min_p, max_p;
			if (p < l - p) {
				min_p = p;
				max_p = l - p;
			}
			else {
				min_p = l - p;
				max_p = p;
			}
			mini = max(mini, min_p);
			maxi = max(maxi, max_p);
		}
		cout << mini << " " << maxi << "\n";
	}
	return 0;
}