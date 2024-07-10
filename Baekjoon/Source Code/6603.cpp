// 2020KB, 0ms
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int k{};
vector<int> S, indexes;

void DFS(int curr) {
	if (static_cast<int>(indexes.size()) == 6) {
		for (int& i : indexes) cout << S[i] << ' ';
		cout << '\n';
		return;
	}
	if (curr == k) return;
	for (int i{ curr }; i < k; ++i) {
		indexes.push_back(i);
		DFS(i + 1);
		indexes.pop_back();
	}
}

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	while (1) {
		cin >> k;
		if (k == 0) break;
		S.assign(k, 0);
		for (int& s : S) cin >> s;
		DFS(0);
		cout << '\n';
	}
	return 0;
}