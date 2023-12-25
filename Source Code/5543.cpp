#include <iostream>
#include <algorithm>

using namespace std;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	
	int s, j, h;
	cin >> s >> j >> h;
	int coke, cider;
	cin >> coke >> cider;

	cout << min({ s + coke - 50, s + cider - 50,j + coke - 50,j + cider - 50,h + coke - 50,h + cider - 50 }) << '\n';

	return 0;
}