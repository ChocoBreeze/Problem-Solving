#include <iostream>
#include <algorithm>

using namespace std;

int main() {
	cin.tie(NULL)->sync_with_stdio(false);
	int N;
	cin >> N;
	int minX, minY, maxX, maxY;
	for (int n = 0; n < N; ++n) {
		int x, y;
		cin >> x >> y;
		if (!n) {
			minX = x;
			maxX = x;
			minY = y;
			maxY = y;
		}
		minX = min(minX, x);
		minY = min(minY, y);
		maxX = max(maxX, x);
		maxY = max(maxY, y);
	}
	cout << (maxX - minX) * (maxY - minY) << '\n';
	return 0;
}