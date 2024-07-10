// Fenwick Tree
// Range Update & Point Query
// https://www.acmicpc.net/blog/view/88
// 5740KB, 192ms

#include <iostream>
#include <vector>

using namespace std;

int sum(vector<int>& tree, int i) {
	int ret{};
	while (i > 0) {
		ret ^= tree[i];
		i -= (i & -i);
	}
	return ret;
}
void update(vector<int>& tree, int i, int diff) {
	for (int e{ static_cast<int>(tree.size()) }; i < e;i += (i & -i)) {
		tree[i] ^= diff;
	}
}

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int n{}; cin >> n;
	vector<int> A(n + 1, 0), tree(n + 1, 0);
	for (int i{ 1 }; i <= n; ++i) {
		cin >> A[i];
		update(tree, i, A[i] ^ A[i - 1]);
	}
	int m{}; cin >> m;
	while (m--) {
		int t{}; cin >> t;
		if (t == 1) {
			int a{}, b{}, c{}; cin >> a >> b >> c; ++a, ++b;
			update(tree, a, c);
			update(tree, b + 1, c);
		}
		else {
			int a{}; cin >> a; ++a;
			cout << sum(tree, a) << '\n';
		}
	}

	return 0;
}