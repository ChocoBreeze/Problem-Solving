#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric> // accumulate

using namespace std;

int main() {
	cin.tie(NULL)->sync_with_stdio(false);
	vector<int> vec(5, 0);
	for (auto& v : vec) {
		cin >> v;
	}
	int sum = accumulate(begin(vec), end(vec), 0);
	sort(begin(vec), end(vec));
	cout << sum / 5 << '\n' << vec[2] << '\n';
	
	return 0;
}