// 접근 참고.
// https://justicehui.github.io/koi/2018/11/20/BOJ7578/
#include <iostream>
#include <vector>

using namespace std;
using ll = long long;
// int -> long long
constinit const int SIZE = 1'000'001;

ll Query(vector<ll>& segTree, int s, int e, int tmpN) {
	// [a,b] count
	s += tmpN, e += tmpN;
	ll cnt{};
	while (s <= e) {
		if ((s & 1) == 1) cnt+=segTree[s];
		if ((e & 1) == 0) cnt+=segTree[e];
		s = (s + 1) >> 1;
		e = (e - 1) >> 1;
	}
	return cnt;
}

void Update(vector<ll>& segTree, int idx, int tmpN) {
	idx += tmpN;
	segTree[idx]++;
	idx >>= 1;
	while (idx) {
		segTree[idx] = segTree[ (idx << 1) ] + segTree[ (idx << 1) + 1];
		idx >>= 1;
	}
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	int N{}; cin >> N;

	int tmpN{ 1 };
	while (tmpN < N) tmpN <<= 1;
	tmpN <<= 1;
	vector<ll> segTree(tmpN, 0);
	tmpN >>= 1;

	// 자신보다 앞에 위치한 숫자가 자신보다 뒤의 index로 가는 경우에 개수 세기
	vector<int> A(N, 0), B(N, 0);
	for (int& a : A) cin >> a;
	
	vector<int> DAT(SIZE, 0);

	for (int i{}; i < N; ++i) {
		int in; cin >> in;
		DAT[in] = i; // index
	}

	ll answer{};
	for (int& a : A) {
		answer += Query(segTree, DAT[a] + 1, N - 1, tmpN);
		Update(segTree, DAT[a], tmpN);
	}
	cout << answer << '\n';

	return 0;
}