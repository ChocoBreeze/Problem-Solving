// Parallel Binary Search
// https://m.blog.naver.com/kks227/221410398513
// https://github.com/kks227/BOJ/blob/master/12900/12921.cpp
// 2156KB, 540ms

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;
constinit const int MOD = 1'000'000'007;
struct P {
	int mid, index;
	P(int mid, int index) : mid{ mid }, index{ index } {}
	bool operator<(const P& other) const {
		if (mid == other.mid) return index < other.index;
		return mid < other.mid;
	}
};

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int N{}, x0{}, a{}, b{}, Q{}; cin >> N >> x0 >> a >> b >> Q;
	vector<int> qs(Q, 0);
	for (int& q : qs) cin >> q;

	vector<int> lo(Q, 0), hi(Q, MOD);

	while (1) {
		bool flag{};
		vector<P> p(Q, P(0, 0));
		int pCnt{}, gCnt{};
		for (int q{}; q < Q; ++q) { // mid값 만들기
			if (lo[q] + 1 < hi[q]) {
				flag = true;
				p[pCnt++] = P((lo[q] + hi[q]) / 2, q); // [mid, index]
			}
		}
		if (!flag) break; // 갱신 완료

		sort(begin(p), begin(p) + pCnt);
		vector<int> gVal(Q + 1, 0), gSize(Q + 1, 0); // mid 값 구간, 구간에 속한 데이터 개수
		gVal[0] = p[0].mid;
		gSize[0] = 1;
		for (int i{ 1 }; i < pCnt; ++i) {
			if (p[i].mid == p[i - 1].mid) ++gSize[gCnt];
			else { // 새 값
				gVal[++gCnt] = p[i].mid;
				gSize[gCnt] = 1;
			}
		}
		gVal[++gCnt] = MOD; // 최대 값
		// 마지막에 MOD값 까지 넣어줘야 하기 때문에 Q보다 한 개 더 많게 gVal 잡아야 함.

		// 해당 구간에 속하는 index 갱신
		vector G = vector(gCnt, vector<int>());
		for (int i{}, j{}; i < gCnt; ++i) {
			vector<int> vec(gSize[i]);
			for (int k{}; k < gSize[i]; ++k) {
				vec[k] = p[j++].index;
			}
			G[i].swap(vec);
		}

		// cnt[i] : the number of values that gVal[i-1] < x <= gVal[i]
		vector<int> cnt(gCnt + 1, 0), pSum(gCnt + 1, 0);
		int x{ x0 };

		for (int n{}; n < N; ++n) { // 개수 만들기
			// value보다 큰 값이 처음으로 나오는 구간.
			// 1번 index부터 하려고 upper_bound 쓴 듯
			++cnt[distance(begin(gVal), upper_bound(begin(gVal), begin(gVal) + gCnt, x))];
			x = (1LL * x * a + b) % MOD;
		}
		for (int i{}; i < gCnt; ++i) {
			pSum[i + 1] = pSum[i] + cnt[i]; // 개수 누적
			for (int j{}; j < gSize[i]; ++j) {
				int& k = G[i][j]; // gCnt[i]에 속한 index들
				(pSum[i + 1] > qs[k] ? hi[k] : lo[k]) = gVal[i]; // 갱신
			}
		}
	}
	cout << accumulate(begin(lo), end(lo), 0LL) << '\n';
	return 0;
}