// 두 수의 차이
#include <iostream>
#include <cstdlib>

using namespace std;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	long long N{}, M{};
	cin >> N >> M;
	cout << abs(N - M) << '\n';
	return 0;
}