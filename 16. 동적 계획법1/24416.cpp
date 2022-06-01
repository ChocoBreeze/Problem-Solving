#include<iostream>
using std::cin;
using std::cout;
int main() {
	cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	int n;
	cin >> n;
	// code 1 : n번째 피보나치 수
	// code 2 : n-2 (재귀에 있는 거 카운팅하고 있었네..)
	int a, b;
	a = b = 1;
	for (int i = 3; i <= n; ++i) {
		int temp = a + b;
		a = b;
		b = temp;
	}
	cout << b << " " << n - 2;
	return 0;
}