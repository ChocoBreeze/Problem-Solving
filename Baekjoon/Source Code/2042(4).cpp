// Sqrt Decomposition
// https://justicehui.github.io/medium-algorithm/2019/03/03/SqrtDecomposition/
// https://www.acmicpc.net/problem/2042
// 9848KB, 404ms

#include <iostream>
#include <vector>
#include <cmath> // sqrt

using namespace std;
using ll = long long;
int N, sq{};

void Init(vector<ll>& arr, vector<ll>& bucket) {
	for (int i{1}; i <= N; ++i) {
		bucket[i / sq] += arr[i];
	}
}

void Update(ll idx, ll val, vector<ll>& arr, vector<ll>& bucket) { // O(sqrt(N))
	arr[idx] = val; // 갱신
	int id = static_cast<int>(idx / sq);
	int s{ id * sq }, e{ s + sq };
	bucket[id] = 0;
	for (int i{ s }; i < e; ++i) {
		bucket[id] += arr[i];
	}
}

ll Query(ll l, ll r, vector<ll>& arr, vector<ll>& bucket) {
	ll ret{};
	while (l % sq != 0 && l <= r) ret += arr[l++]; // 왼쪽 미포함 구간
	while ((r + 1) % sq != 0 && l <= r) ret += arr[r--]; // 오른쪽 미포함 구간

	while (l <= r) { // 완전히 커버되는 구간은 bucket으로 구하기
		ret += bucket[l / sq];
		l += sq;
	}

	return ret;
}

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int M{}, K{}; cin >> N >> M >> K;
	sq = static_cast<int>(sqrt(N));

	vector<ll> arr(N + 1, 0), bucket(N / sq + 1, 0); // arr : 1 base, bucket : 0 base
	for (int n{ 1 }; n <= N; ++n) cin >> arr[n];
	Init(arr, bucket);
	
	for (int q{}; q < M + K; ++q) {
		ll a{}, b{}, c{}; cin >> a >> b >> c;
		if (a == 1) {
			Update(b, c, arr, bucket);
		}
		else {
			cout << Query(b, c, arr, bucket) << '\n';
		}
	}

	return 0;
}