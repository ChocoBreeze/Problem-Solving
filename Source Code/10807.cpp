#include <iostream>
#include <vector>

using namespace std;

int main() {
	cin.tie(NULL)->sync_with_stdio(false);
	int N, v, answer = 0;
	cin >> N;
	vector<int> vec(N, 0);
	for (auto& i : vec) {
		cin >> i;
	}
	cin >> v;
	for (auto& i : vec) {
		if (i == v) ++answer;
	}
	cout << answer << '\n';
	return 0;
}