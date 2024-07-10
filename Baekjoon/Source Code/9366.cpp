// 2020KB, 0ms
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int T{}; cin >> T;
	vector<int> edges(3,0);
	for (int tc{ 1 }; tc <= T; ++tc) {
		cin >> edges[0] >> edges[1] >> edges[2];
		sort(begin(edges), end(edges));

		cout << "Case #" << tc << ": ";
		if (edges[0] + edges[1] <= edges[2]) cout << "invalid!\n";
		else if (edges[0] == edges[1] && edges[0] == edges[2]) cout << "equilateral\n";
		else if (edges[0] == edges[1] || edges[1] == edges[2] || edges[2] == edges[0]) cout << "isosceles\n";
		else cout << "scalene\n";
	}

	return 0;
}