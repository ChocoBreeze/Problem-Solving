#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	cin.tie(NULL) -> sync_with_stdio(false);
	int N;
	cin >> N;
	vector<int> coord(N, 0);
	vector<int> coord_;
	for (auto& i : coord) {
		cin >> i;
	}
	coord_.assign(begin(coord), end(coord));
	sort(begin(coord_), end(coord_)); // sort
	coord_.erase(unique(begin(coord_), end(coord_)), end(coord_)); // 중복제거
	
	for (auto& i : coord) {
		auto it = lower_bound(begin(coord_), end(coord_), i);
		cout << distance(begin(coord_), it) << " ";
	}
	return 0;
}