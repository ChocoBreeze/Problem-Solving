#include <iostream>

using namespace std;

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	int n;
	cin >> n;
	int a = 0, b = 1;
	for (int i = 0; i < n - 1; ++i) {
		int temp = b;
		b = a + b;
		a = temp;
	}
	cout << b;
	return 0;
}