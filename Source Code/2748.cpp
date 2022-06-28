#include<iostream>
// 숫자 범위
using std::cin;
using std::cout;

int main() {
	cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	int n;
	cin >> n;
	long long f0 = 0, f1 = 1;
	for (int i = 1; i < n; ++i) {
		long long fn = f0 + f1;
		f0 = f1;
		f1 = fn;
	}
	if (n == 0) cout << f0;
	else if (n == 1) cout << f1;
	else cout << f1;
	return 0;
}