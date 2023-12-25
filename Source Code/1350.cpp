#include <iostream>
#include <vector>

using namespace std;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int N{}; cin >> N;
	vector<int> files(N, 0);
	for (int& f : files) {
		cin >> f;
	}
	int cluster{}; cin >> cluster;
	long long answer{};
	for (int& f : files) {
		if (f % cluster == 0) {
			answer += (static_cast<long long>(f / cluster));
		}
		else {
			answer += (static_cast<long long>(f / cluster)) + 1;
		}
	}
	answer *= cluster;
	cout << answer << '\n';

	return 0;
}