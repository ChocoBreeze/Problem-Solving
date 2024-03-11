// Parallel Binary Search
// https://m.blog.naver.com/kks227/221410398513
// https://github.com/encrypted-def/BOJ/blob/master/12921.cpp
// 2156KB, 732ms

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
constinit const int MOD = 1'000'000'007;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int N{}, X0{}, A{}, B{}, Q{}; cin >> N >> X0 >> A >> B >> Q;
	vector<int> queries(Q, 0);
	vector<int> lo(Q, 0), hi(Q, MOD - 1), mid(Q, (MOD - 1) / 2);
	for (int& query : queries) {
		cin >> query; 
		query++;
	}
	sort(begin(queries), end(queries)); // 숫자 합만 구하면 되니까 정렬해버림

	int isDone{};
	while (!isDone) {
		vector<int> delta(Q + 1, 0);
		isDone = 1;
		int arr = X0;
		for (int n{}; n < N; ++n) {
			int r = static_cast<int>(distance(begin(mid), lower_bound(begin(mid), end(mid), arr)));
			delta[r]++; // 이 구간에 속한 개수 카운팅
			arr = (1LL * arr * A + B) % MOD;
		}
		int cnt{};
		for (int q{}; q < Q; ++q) {
			cnt += delta[q]; // 해당 구간에 속한 개수누적
			if (lo[q] == hi[q]) continue; // 갱신 완료

			if (cnt > queries[q]) hi[q] = mid[q] - 1;
			else if (cnt == queries[q]) hi[q] = mid[q];
			else lo[q] = mid[q] + 1;

			mid[q] = (lo[q] + hi[q]) >> 1;
			if (lo[q] != hi[q]) isDone = 0;
		}
	}

	long long tot{};
	for (auto& l : lo) tot += l;
	cout << tot << '\n';

	return 0;
}