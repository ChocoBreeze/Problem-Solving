// 5928KB, 124ms
#include <iostream>
#include <vector>

using namespace std;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int N{}; cin >> N;
	vector<int> testRoom(N, 0);
	for (int& tr : testRoom) cin >> tr;
	int B{}, C{}; cin >> B >> C;

	long long sum{};
	for (int& tr : testRoom) {
		if (tr <= B) ++sum; // 총감독관
		else {
			++sum; // 총감독관
			sum += static_cast<long long>(tr - B) / C; // 부감독관
			if ((tr - B) % C) ++sum;
		}
	}
	cout << sum << '\n';
	return 0;
}