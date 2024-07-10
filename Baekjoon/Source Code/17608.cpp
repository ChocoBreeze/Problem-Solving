#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int N{}; cin >> N;
	vector<int> hs(N, 0);
	for (int& h : hs) cin >> h;

	int answer{}, maxH{ -1 };
	reverse(begin(hs), end(hs));
	for (int& h : hs) {
		if (maxH < h) {
			maxH = h;
			++answer;
		}
	}
	cout << answer << '\n';

	return 0;
}