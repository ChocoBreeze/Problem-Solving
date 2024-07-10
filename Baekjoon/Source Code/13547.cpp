// 평방 분할, Mo's 공부..
// https://m.blog.naver.com/kks227/221401154455
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;
constinit const int MAXA = 1'000'010;
int sqrtN;

// 쿼리 정렬을 위한 쿼리 구조체
struct QueryNode {
	int s, e, n; // 시작, 끝, 쿼리 번호
	QueryNode() = default;
	QueryNode(int s, int e, int n) : s(s), e(e), n(n) {}
	// (s/√N, e) 순으로 오름차순 정렬
	bool operator<(const QueryNode& other) const {
		if (s / sqrtN != other.s / sqrtN) return (s / sqrtN < other.s / sqrtN);
		return e < other.e;
	}
};

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int N{}; cin >> N;
	vector<int> A(N, 0);
	for (int& a : A) cin >> a;
	sqrtN = static_cast<int>(sqrt(N));

	int M{}; cin >> M;
	// 쿼리를 입력받은 후 정렬
	vector<QueryNode> queries(M);
	for (int m{}; m < M;++m) {
		QueryNode& q = queries[m];
		cin >> q.s >> q.e;
		q.s--; // [q.s, q.e) 구간으로 변경
		q.n = m;
	}
	sort(begin(queries), end(queries));
	
	// 첫 쿼리는 손수 구하기
	int nowCnt{};
	vector<int> cnt(MAXA, 0), result(M, 0);
	auto& [s, e, n] = queries[0];
	for (int i = s; i < e; ++i) {
		if (cnt[A[i]]++ == 0) ++nowCnt;
	}
	result[n] = nowCnt;

	// 두 번째 쿼리부터 이전의 결과를 이용!
	// [queries[m].s, queries[m].e)
	for (int m{ 1 }; m < M; ++m) {
		// 이전 쿼리보다 s가 작을 경우 왼쪽으로 구간을 확장하며 더함
		while (queries[m].s < s) if (cnt[A[--s]]++ == 0) ++nowCnt; // 범위 확장 후 구간 확인
		// 이전 쿼리보다 e가 클 경우 오른쪽으로 구간을 확장하며 더함
		while (e < queries[m].e) if (cnt[A[e++]]++ == 0) ++nowCnt; // 기존 구간 확인 후 범위 확장
		// 이전 쿼리보다 s가 클 경우 구간을 왼쪽으로부터 축소하며 뺌
		while (queries[m].s > s) if (--cnt[A[s++]] == 0) --nowCnt; // 기존 구간 확인 후 범위 축소
		// 이전 쿼리보다 e가 작을 경우 구간을 오른쪽으로부터 축소하며 뺌
		while (e > queries[m].e) if (--cnt[A[--e]] == 0) --nowCnt; // 범위 축소 후 구간 확인
		// 이번 쿼리의 결과 완성
		result[queries[m].n] = nowCnt;
	}

	for (int m{}; m < M; ++m) {
		cout << result[m] << '\n';
	}

	return 0;
}