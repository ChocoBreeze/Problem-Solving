#include <iostream>

using namespace std;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int N{}; cin >> N;

	int sum{}, sumSquare{}, cubeSum{};

	for (int i{}; i <= N; ++i) {
		sum += i;
		cubeSum += i * i * i;
	}
	sumSquare = sum * sum;

	cout << sum << '\n' << sumSquare << '\n' << cubeSum << '\n';
	return 0;
}