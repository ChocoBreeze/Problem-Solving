// Square Root Decomposition, Mo's Algorithm
// https://m.blog.naver.com/kks227/221401154455

#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;
using ll = long long;

/*
모든 쿼리 Q = (s, e)에 대해,?([s/√N], e) 순으로 오름차순 정렬
위에서 말한 대로 바로 이전 쿼리의 결과를 재사용
*/

int sqrtN;
// 쿼리 정렬을 위한 쿼리 구조체
struct QueryNode {
	int s, e, n; // n은 쿼리 번호
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

	int N{}, M{}; cin >> N >> M;
	vector<int> vec(N, 0);
	for (int& v : vec) cin >> v;

	sqrtN = static_cast<int>(sqrt(N));

	vector<QueryNode> queries(M);
	for (int m{}; m < M;++m) {
		cin >> queries[m].s >> queries[m].e;
		queries[m].s--;
		queries[m].n = m;
	}
	sort(begin(queries), end(queries));

	// 첫 번째에 위치한 쿼리의 결과는 손수 구함
	ll sum{};
	vector<ll> result(M, 0);
	auto& [s, e, n] = queries[0];
	for (int i{ s }; i < e; ++i) {
		sum += vec[i];
	}
	result[n] = sum;

	// 다음 쿼리부터, 바로 이전 쿼리의 결과를 사용해 계산!
	for (int i{ 1 }; i < M; ++i) {
		// 이전 쿼리보다 s가 작을 경우 왼쪽으로 구간을 확장하며 더함
		while (queries[i].s < s) sum += vec[--s];
		// 이전 쿼리보다 e가 클 경우 오른쪽으로 구간을 확장하며 더함
		while (e < queries[i].e) sum += vec[e++];
		// 이전 쿼리보다 s가 클 경우 구간을 왼쪽으로부터 축소하며 뺌
		while (queries[i].s > s) sum -= vec[s++];
		// 이전 쿼리보다 e가 작을 경우 구간을 오른쪽으로부터 축소하며 뺌
		while (e > queries[i].e) sum -= vec[--e];
		// 이번 쿼리의 결과 완성
		result[queries[i].n] = sum;
	}

	// 모인 결과를 한 번에 처리
	for (int m{}; m < M; ++m) {
		cout << result[m] << '\n';
	}

	return 0;
}