/*
1 : 1
2 : 3
3 : (2) + 2*(1) = 3 + 2 = 5
4 : (3) + 2*(2) = 5 + 6 = 11
5 : (4) + 2*(3) = 11 + 10 = 21
6 : (5) + 2*(4) = 21 + 22 = 43
7 : (6) + 2*(5) = 43 + 42 = 85
8 : (7) + 2*(6) = 85 + 86 = 171
*/
#include<iostream>
using std::cin;
using std::cout;
int main() {
	cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	int n;
	cin >> n;
	int a = 1, b = 3; // base case
	for (int i = 0; i < n - 2; ++i) {
		int temp = (b + 2 * a) % 10007;
		a = b;
		b = temp;
	}
	if (n == 1) cout << a;
	else cout << b;
	return 0;
}