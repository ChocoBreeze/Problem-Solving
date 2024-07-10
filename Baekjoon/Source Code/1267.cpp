#include <iostream>
#include <algorithm>

using namespace std;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int N{}, Y{}, M{};
	cin >> N;
	for (int n{}; n < N; ++n) {
		int times;
		cin >> times;
		Y += ((times / 30) + 1) * 10;
		M += ((times / 60) + 1) * 15;
	}
	if (Y == M) {
		cout << "Y M " << Y << '\n';
	}
	else if (Y < M) {
		cout << "Y " << Y << '\n';
	}
	else {
		cout << "M " << M << '\n';
	}

	return 0;
}