// 2020KB, 8ms
#include <iostream>

using namespace std;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int A{}, B{}, N{}; cin >> A >> B >> N;
	A %= B;
	int answer{};
	for (int n{}; n < N; ++n) {
		A *= 10, answer = A / B, A %= B;
	}
	cout << answer << '\n';
	return 0;
}