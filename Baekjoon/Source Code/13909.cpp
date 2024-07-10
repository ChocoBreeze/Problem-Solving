// 약수 개수가 홀수이면 열려 있음.
// 제곱수

#include <iostream>

using namespace std;

int main() {
	long long N{};
	cin >> N;
	cin.tie(NULL)->sync_with_stdio(false);

	int cnt{};
	long long root = 1;
	for (;;) {
		if (root * root > N) break;
		++cnt;
		++root;
	}
	cout << cnt << '\n';

	return 0;
}