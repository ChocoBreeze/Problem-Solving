#include<iostream>

using namespace std;

int main() {
	cin.tie(NULL)->sync_with_stdio(false);
	int X, answer = 0;
	cin >> X;
	for (; X > 0; X >>= 1) {
		if (X & 1) ++answer;
	}
	cout << answer;
	return 0;
}