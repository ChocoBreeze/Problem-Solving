#include <iostream>
#include <vector>

using namespace std;
constinit const int SIZE = 20; // 1 << 19 = 524288

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int m{}; cin >> m;

	vector<vector<int>> lcaT(SIZE, vector<int>(m + 1, 0));

	for (int i = 1; i <= m; ++i) {
		cin >> lcaT[0][i];
	}

	for (int s = 1; s < SIZE; ++s) {
		for (int i = 1; i <= m; ++i) {
			lcaT[s][i] = lcaT[s - 1][lcaT[s - 1][i]];
		}
	}

	int Q{}; cin >> Q;
	while (Q--) {
		int n{}, x{}; cin >> n >> x;

		for (int i{}; i < SIZE; ++i) {
			if ((n >> i) & 1) x = lcaT[i][x];
		}
		cout << x << '\n';
	}

	return 0;
}