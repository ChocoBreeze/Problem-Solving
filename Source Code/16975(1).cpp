// Fenwick Tree With Lazy Propagation
// https://rebro.kr/94
// https://www.acmicpc.net/problem/10999
// 3588KB, 48ms

#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

ll sum(vector<ll>& tree, ll i) { 
	ll ans{};
	while (i > 0) {
		ans += tree[i];
		i -= (i & -i);
	}
	return ans;
}
void update(vector<ll>& tree, ll i, ll diff) { 
	while (i < static_cast<ll>(tree.size())) { // i <= N
		tree[i] += diff;
		i += (i & -i);
	}
}

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int N{}, M{}; cin >> N;
	// 1번 인덱스 base
	vector<ll> A(N + 1, 0), tree(N + 1, 0);
	for (int i{ 1 }; i <= N; ++i) {
		cin >> A[i];
		update(tree, i, A[i] - A[i-1]);
	}

	cin >> M;
	for (int m{}; m < M; ++m) {
		ll a{}; cin >> a;
		if (a == 1) { // [i, j]에 k 더하기 - Range Update
			int i{}, j{}, k{}; cin >> i >> j >> k; 
			update(tree, i, k);
			update(tree, j + 1, -k);
		}
		else { // a == 2 : x번째 수 - Point Query
			ll x{}; cin >> x;
			cout << sum(tree, x) << '\n';
		}
	}

	return 0;
}