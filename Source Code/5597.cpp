#include <iostream>
#include <vector>

using namespace std;

int main() {
	cin.tie(NULL)->sync_with_stdio(false);
	vector<bool> vec(31, false);
	int tmp;
	for (int i = 0; i < 28;++i) {
		cin >> tmp;
		vec[tmp] = true;
	}
	for (int i = 1; i < 31; ++i) {
		if (!vec[i]) cout << i << '\n';
	}
	return 0;
}