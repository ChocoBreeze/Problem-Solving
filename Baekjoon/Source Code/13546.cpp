// https://m.blog.naver.com/kks227/221401154455
// Sqrt Decomposition
// [1, K] 사이의 값을 가지는 index를 deque로 관리
// 매 쿼리마다 [1, K]를 빠르게 확인해서 front, back의 최대 차 찾는 방법?
// => sqrt decomposition 이용

// 단순히 K로 bucket 만들어서 갱신 => TLE
// bucket을 K값으로 올리지 말고, | x - y |의 값으로 올리기 => 카운팅
// https://github.com/kks227/BOJ/blob/master/13500/13546.cpp
// 70524KB, 2576ms

#include <iostream>
#include <vector>
#include <cmath> // sqrt
#include <algorithm> // sort, max
#include <queue> // deque
#include <cassert>

using namespace std;
constinit const int MAX = 100'000;
constinit const int MAX_SQRT = 316;
constinit const int MAX_SQD = (MAX - 1) / MAX_SQRT + 1;
constinit const int MAX_CAP = MAX_SQRT * MAX_SQD;

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
	// sqrtK = static_cast<int>(sqrt(K));
	// const int BUCKETSIZE = K / sqrtK + 1;
	vector<int> A(N + 1, 0), bucket(MAX_SQD, 0), cnt(MAX_CAP, 0);
	for (int n{}; n < N; ++n) {
		cin >> A[n];
		--A[n];
	}
	int M{}; cin >> M;

	vector<QueryNode> qs(M);
	vector<deque<int>> dqs(K + 1); // 1 ~ K
	for (int m{}; m < M; ++m) {
		auto& q = qs[m]; qs[m].n = m;
		cin >> q.s >> q.e;
		--q.s;
	}

	sort(begin(qs), end(qs));
	// 첫 쿼리 손수 구하기
	vector<int> answers(M);
	int s{}, e{};

	for (int m{}; m < M; ++m) {
		auto& [ss, ee, n] = qs[m]; // 새 구간
		while (ss < s) { // 왼쪽 구간 확장
			--s;
			// 기존 구간 갱신
			int diff{};
			if (!dqs[A[s]].empty()) {
				diff = dqs[A[s]].back() - dqs[A[s]].front();
				--cnt[diff];
				--bucket[diff / MAX_SQRT];
			}
			// 새 구간 반영
			dqs[A[s]].push_front(s);
			diff = dqs[A[s]].back() - dqs[A[s]].front();
			++cnt[diff];
			++bucket[diff / MAX_SQRT];
		}
		while (e < ee) { // 오른쪽 구간 확장
			int diff{};
			// 기존 구간 갱신
			if (!dqs[A[e]].empty()) { 
				diff = dqs[A[e]].back() - dqs[A[e]].front();
				--cnt[diff];
				--bucket[diff / MAX_SQRT];
			}
			// 새 구간 반영
			dqs[A[e]].push_back(e);
			diff = dqs[A[e]].back() - dqs[A[e]].front();
			++cnt[diff];
			++bucket[diff / MAX_SQRT];
			++e;
		}
		while (ss > s) { // 왼쪽 구간 축소
			int diff{};
			// 기존 구간 갱신
			diff = dqs[A[s]].back() - dqs[A[s]].front();
			--cnt[diff];
			--bucket[diff / MAX_SQRT];
			// 새 구간 반영
			dqs[A[s]].pop_front();
			if (!dqs[A[s]].empty()) {
				diff = dqs[A[s]].back() - dqs[A[s]].front();
				++cnt[diff];
				++bucket[diff / MAX_SQRT];
			}
			++s;
		}
		while (e > ee) { // 오른쪽 구간 축소
			--e;
			int diff{};
			// 기존 구간 갱신
			diff = dqs[A[e]].back() - dqs[A[e]].front();
			--cnt[diff];
			--bucket[diff / MAX_SQRT];
			dqs[A[e]].pop_back();
			// 새 구간 반영
			if (!dqs[A[e]].empty()) {
				diff = dqs[A[e]].back() - dqs[A[e]].front();
				++cnt[diff];
				++bucket[diff / MAX_SQRT];
			}
		}
		// 갱신을 빠르게 하는 방법?
		// bucket값 확인 => 1보다 크면 => 세부적인 값 확인
		// 큰 값부터 확인해서 최대값 찾으면 break
		answers[n] = [&]() -> int {
			for (int b{ MAX_SQD - 1 }; b >= 0; --b) {
				if (!bucket[b]) continue;
				for (int k{ MAX_SQRT - 1 }; k >= 0; --k) {
					if (cnt[b * MAX_SQRT + k] > 0) {
						return b * MAX_SQRT + k;
					}
				}
			}
			return 0;
		} ();
	}
	
	for (int& ans : answers) cout << ans << '\n';

	return 0;
}