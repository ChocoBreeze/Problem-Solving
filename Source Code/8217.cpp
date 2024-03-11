// Fenwick Tree(Range Update & Range Query)
// https://www.acmicpc.net/blog/view/88
// https://everenew.tistory.com/114
// Parallel Binary Search
// https://m.blog.naver.com/kks227/221410398513
// 37832KB, 2376ms

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using ll = long long;

struct Query {
	int l, r, a;
	Query(int l, int r, int a) : l{ l }, r{ r }, a{ a } {}
};

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
void RangeUpdate(vector<ll>& linearTree, vector<ll>& constantTree, ll L, ll R, ll x) {
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
	int N{}, M{}; cin >> N >> M; // 회원국 개수, 행성 궤도의 구역 개수
	vector<vector<int>> areaList(M + 1); // areaList[i] : i번째 회원국이 담당한 구역들
	for (int m{ 1 }; m <= M; ++m) {
		int o{}; cin >> o; o--; // 0 based index
		areaList[o].push_back(m);
	}
	vector<int> P(N, 0); // BIU 회원국이 목표치로 정한 운석 샘플 수량
	for (int& p : P) cin >> p;
	int Q{}; cin >> Q; // 유성우 예보의 수(날짜 수)
	vector<Query> queries(Q, Query(0,0,0));
	for (auto& [l, r, a] : queries) cin >> l >> r >> a;
	
	vector<int> lo(N, 0), hi(N, Q + 1); // N개의 회원국에 대해 lo, hi 초기화
	while (1) {
		bool isFinish{ true };
		vector mids(Q + 1, vector<int>());
		for (int n{}; n < N; ++n) {
			if (lo[n] + 1 < hi[n]) { // 아직 답을 못 찾은 애들
				isFinish = false;
				int mid = lo[n] + (hi[n] - lo[n]) / 2;
				mids[mid].push_back(n);
			}
		}

		if (isFinish) break;
		vector<ll> linearTree(M + 1, 0), constantTree(M + 1, 0);
		for (int q{}; q < Q; ++q) { // 날짜 지나감에 따라 쿼리 처리
			auto& [l, r, a] = queries[q];
			if (l <= r) {
				RangeUpdate(linearTree, constantTree, l, r, a);
			}
			else { // l > r
				RangeUpdate(linearTree, constantTree, l, M, a);
				RangeUpdate(linearTree, constantTree, 1, r, a);
			}

			// mid가 q + 1인 쿼리들 처리
			for (int idx : mids[q + 1]) { // 0 based
				// idx에 속한 구역들 합
				ll sum{};
				for (int& area : areaList[idx]) {
					sum += RangeSum(linearTree, constantTree, area, area);
					if (sum >= P[idx]) break; // long long 넘어갈 수도 있음.
				}
				if (sum >= P[idx]) { // 목표치 넘긴 경우 => hi 갱신
					hi[idx] = q + 1;
				}
				else { // lo 갱신
					lo[idx] = q + 1;
				}
			}
		}
	}

	for (int n{}; n < N; ++n) {
		if (lo[n] == Q) cout << "NIE\n";
		else cout << hi[n] << '\n';
	}

	return 0;
}