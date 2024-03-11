// https://m.blog.naver.com/kks227/221401154455
// Sqrt Decomposition
// [1, K] 사이의 값을 가지는 index를 deque로 관리
// 매 쿼리마다 [1, K]를 빠르게 확인해서 front, back의 최대 차 찾는 방법?
// => sqrt decomposition 이용

// 단순히 K로 bucket 만들어서 갱신 => TLE
// bucket을 K값으로 올리지 말고, | x - y |의 값으로 올리기 => 카운팅
// https://github.com/kks227/BOJ/blob/master/13500/13546.cpp
// list 도입
// 9280KB, 1792ms

#include <iostream>
#include <vector>
#include <cmath> // sqrt
#include <algorithm> // sort, max
#include <list> // list

using namespace std;

int N{}, K{};
int sqrtN{};
// 쿼리 정렬을 위한 쿼리 struct
struct QueryNode {
	int s, e, n; // n은 쿼리 번호
	QueryNode() : QueryNode(0, 0, -1) {}
	QueryNode(int s1, int e1, int n1) : s{ s1 }, e{ e1 }, n{ n1 } {}
	// (s/√N, e) 순으로 오름차순 정렬
	bool operator <(const QueryNode& O) const {
		if (s / sqrtN != O.s / sqrtN) return (s / sqrtN < O.s / sqrtN);
		return (e < O.e);
	}
};

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	cin >> N >> K;
	sqrtN = static_cast<int>(sqrt(N));
	const int BUCKETSIZE = N / sqrtN + 1; // 100'000 => 317
	vector<int> A(N + 1, 0), bucket(BUCKETSIZE, 0), cnt(sqrtN * BUCKETSIZE, 0);
	// 바보 - K로 BUCKETSIZE 잡으면 안 되는 구나,,
	// 둘의 index 차이를 index로 계산해야 하는데 K로 BUCKETSIZE 잡을 수 없음,,
	for (int n{}; n < N; ++n) {
		cin >> A[n];
		--A[n];
	}
	int M{}; cin >> M;

	vector<QueryNode> qs(M);
	vector<list<int>> lists(K + 1); // 1 ~ K
	for (int m{}; m < M; ++m) {
		auto& q = qs[m]; qs[m].n = m;
		cin >> q.s >> q.e;
		--q.s;
	}

	sort(begin(qs), end(qs));
	vector<int> answers(M);
	int s{}, e{};

	for (int m{}; m < M; ++m) {
		auto& [ss, ee, n] = qs[m]; // 새 구간
		while (ss < s) { // 왼쪽 구간 확장
			--s;
			// 기존 구간 갱신
			int diff{};
			if (!lists[A[s]].empty()) {
				diff = lists[A[s]].back() - lists[A[s]].front();
				--cnt[diff];
				--bucket[diff / sqrtN];
			}
			// 새 구간 반영
			lists[A[s]].push_front(s);
			diff = lists[A[s]].back() - lists[A[s]].front();
			++cnt[diff];
			++bucket[diff / sqrtN];
		}
		while (e < ee) { // 오른쪽 구간 확장
			int diff{};
			// 기존 구간 갱신
			if (!lists[A[e]].empty()) { 
				diff = lists[A[e]].back() - lists[A[e]].front();
				--cnt[diff];
				--bucket[diff / sqrtN];
			}
			// 새 구간 반영
			lists[A[e]].push_back(e);
			diff = lists[A[e]].back() - lists[A[e]].front();
			++cnt[diff];
			++bucket[diff / sqrtN];
			++e;
		}
		while (ss > s) { // 왼쪽 구간 축소
			int diff{};
			// 기존 구간 갱신
			diff = lists[A[s]].back() - lists[A[s]].front();
			--cnt[diff];
			--bucket[diff / sqrtN];
			// 새 구간 반영
			lists[A[s]].pop_front();
			if (!lists[A[s]].empty()) {
				diff = lists[A[s]].back() - lists[A[s]].front();
				++cnt[diff];
				++bucket[diff / sqrtN];
			}
			++s;
		}
		while (e > ee) { // 오른쪽 구간 축소
			--e;
			int diff{};
			// 기존 구간 갱신
			diff = lists[A[e]].back() - lists[A[e]].front();
			--cnt[diff];
			--bucket[diff / sqrtN];
			lists[A[e]].pop_back();
			// 새 구간 반영
			if (!lists[A[e]].empty()) {
				diff = lists[A[e]].back() - lists[A[e]].front();
				++cnt[diff];
				++bucket[diff / sqrtN];
			}
		}
		// 갱신을 빠르게 하는 방법?
		// bucket값 확인 => 1보다 크면 => 세부적인 값 확인
		// 큰 값부터 확인해서 최대값 찾으면 break
		answers[n] = [&]() -> int {
			for (int b{ BUCKETSIZE - 1 }; b >= 0; --b) {
				if (!bucket[b]) continue;
				for (int k{ sqrtN - 1 }; k >= 0; --k) {
					if (cnt[b * sqrtN + k] > 0) {
						return b * sqrtN + k;
					}
				}
			}
			return 0;
		} ();
	}
	
	for (int& ans : answers) cout << ans << '\n';

	return 0;
}