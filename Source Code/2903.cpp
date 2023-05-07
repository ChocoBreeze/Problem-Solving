/*
2 * 2
3 * 3
5 * 5
9 * 9
17 * 17
33 * 33
*/
#include <iostream>

using namespace std;

int main() {
	int N, side = 3;
	cin.tie(NULL)->sync_with_stdio(false);
	cin >> N;
	for (int n = 1; n < N; ++n) {
		side = side * 2 - 1;
	}
	cout << side * side << '\n';
	
	return 0;
}