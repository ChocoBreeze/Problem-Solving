// Fenwick Tree With Lazy Propagation
// https://www.acmicpc.net/blog/view/88
// https://everenew.tistory.com/114
// https://www.acmicpc.net/problem/10999

// Range Update & Range Query
// 25468KB, 240ms

#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

ll Sum(vector<ll>& tree, ll i) { 
	ll ans{};
	while (i > 0) {
		ans += tree[i];
		i -= (i & -i);
	}
	return ans;
}
void Update(vector<ll>& tree, ll i, ll diff) { 
	while (i < static_cast<ll>(tree.size())) { // i <= N
		tree[i] += diff;
		i += (i & -i);
	}
}
void RangeUpdate(vector<ll>&linearTree, vector<ll>&constantTree, ll L, ll R, ll x) {
	Update(linearTree, L, x); // B[L] += x
	Update(linearTree, R + 1, -x); // B[R+1] -= x

	Update(constantTree, L, (-L + 1) * x);
	Update(constantTree, R + 1, (R)*x);
}
ll RangeSum(vector<ll>& linearTree, vector<ll>& constantTree, ll L, ll R) {
	ll ret = Sum(linearTree, R) * R + Sum(constantTree, R); // [1, R]의 구간합
	ret -= Sum(linearTree, L - 1) * (L - 1) + Sum(constantTree, L - 1); // [1, L - 1]의 구간합
	return ret;
}

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int N{}, M{}, K{}; cin >> N >> M >> K;
	// 1번 인덱스 base
	vector<ll> A(N + 1, 0), linearTree(N + 1, 0), constantTree(N+1, 0);
	for (int i{ 1 }; i <= N; ++i) {
		cin >> A[i];
		// Update(tree, i, A[i] - A[i-1]);
		RangeUpdate(linearTree, constantTree, i, i, A[i]);
	}

	for (int m{}; m < M + K; ++m) {
		ll a{}; cin >> a;
		if (a == 1) { // [b, c]에 d 더하기 - Range Update
			ll b{}, c{}, d{}; cin >> b >> c >> d; 
			RangeUpdate(linearTree, constantTree, b, c, d);
		}
		else { // a == 2 : [b, c] 구간 합 구하기
			ll b{}, c{}; cin >> b >> c;
			cout << RangeSum(linearTree, constantTree, b, c) << '\n';
		}
	}

	return 0;
}