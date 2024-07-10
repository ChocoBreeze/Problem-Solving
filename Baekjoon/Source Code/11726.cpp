// dp[n] = dp[n-1]+dp[n-2]
// dp[1] = 1, dp[2] = 2, ...
#include<iostream>

using std::cin;
using std::cout;

int main() {
	cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	long long int n, a = 1, b = 2;
	cin >> n;
	for (int i = 0; i < n - 2; ++i) {
		// 할 때마다 나머지 계산해주기
		long long int temp = (a + b)%10007;
		a = b;
		b = temp;
	}
	if (n == 1) cout << a;
	else cout << b%10007;
	return 0;
}