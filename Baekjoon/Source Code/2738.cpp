#include <iostream>
#include <vector>

using namespace std;

int main() {
	cin.tie(NULL)->sync_with_stdio(false);
	int N, M, tmp;
	cin >> N >> M;
	vector<vector<int>> answer(N,vector<int>(M,0));
	for (auto& i : answer) {
		for (auto& j : i) {
			cin >> j;
		}
	}
	for (auto& i : answer) {
		for (auto& j : i) {
			cin >> tmp;
			j += tmp;
		}
	}
	for (auto& i : answer) {
		for (auto& j : i) {
			cout << j << ' ';
		}
		cout << '\n';
	}

	
	return 0;
}