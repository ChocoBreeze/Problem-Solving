// https://www.acmicpc.net/source/share/60b207768b38411b8bee19d4d799d8ca
// 새로운 풀이!
#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

// n진법 표현 : ... + a_2 * n^2 + a_1 * n^1 + a_0 * n^0

int main() {
	fastio;
	int n, m; cin >> n >> m;
	int lim{ 1 };
	for (int i{}; i < m; ++i) lim *= n;

	vector<int> values(m,0);
	for (int i{}; i < lim; ++i) {
		int curr = i;
		for (int j{}; j < m; ++j) {
			values[j] = curr % n + 1;
			curr /= n;
		}
		for(auto it = rbegin(values);it!=rend(values);++it) cout << *it << ' ';
		cout << '\n';
	}

	return 0;
}