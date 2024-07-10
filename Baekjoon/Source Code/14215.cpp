#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
	vector<int> lens(3, 0);
	for (int& l : lens) cin >> l;
	sort(begin(lens), end(lens));

	if (lens[2] < lens[0] + lens[1]) cout << lens[0] + lens[1] + lens[2] << '\n';
	else cout << (lens[0] + lens[1]) * 2 - 1 << '\n';

	return 0;
}