#include <iostream>

using namespace std;

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	int X, N, a, b;
	cin >> X >> N;
	int sum = 0;
	for (int n = 0; n < N; ++n) {
		cin >> a >> b;
		sum += a * b;
	}
	if (sum == X) cout << "Yes";
	else cout << "No";
	return 0;
}