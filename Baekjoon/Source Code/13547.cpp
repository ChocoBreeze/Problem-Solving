// ��� ����, Mo's ����..
// https://m.blog.naver.com/kks227/221401154455
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;
constinit const int MAXA = 1'000'010;
int sqrtN;

// ���� ������ ���� ���� ����ü
struct QueryNode {
	int s, e, n; // ����, ��, ���� ��ȣ
	QueryNode() = default;
	QueryNode(int s, int e, int n) : s(s), e(e), n(n) {}
	// (s/��N, e) ������ �������� ����
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
	// ������ �Է¹��� �� ����
	vector<QueryNode> queries(M);
	for (int m{}; m < M;++m) {
		QueryNode& q = queries[m];
		cin >> q.s >> q.e;
		q.s--; // [q.s, q.e) �������� ����
		q.n = m;
	}
	sort(begin(queries), end(queries));
	
	// ù ������ �ռ� ���ϱ�
	int nowCnt{};
	vector<int> cnt(MAXA, 0), result(M, 0);
	auto& [s, e, n] = queries[0];
	for (int i = s; i < e; ++i) {
		if (cnt[A[i]]++ == 0) ++nowCnt;
	}
	result[n] = nowCnt;

	// �� ��° �������� ������ ����� �̿�!
	// [queries[m].s, queries[m].e)
	for (int m{ 1 }; m < M; ++m) {
		// ���� �������� s�� ���� ��� �������� ������ Ȯ���ϸ� ����
		while (queries[m].s < s) if (cnt[A[--s]]++ == 0) ++nowCnt; // ���� Ȯ�� �� ���� Ȯ��
		// ���� �������� e�� Ŭ ��� ���������� ������ Ȯ���ϸ� ����
		while (e < queries[m].e) if (cnt[A[e++]]++ == 0) ++nowCnt; // ���� ���� Ȯ�� �� ���� Ȯ��
		// ���� �������� s�� Ŭ ��� ������ �������κ��� ����ϸ� ��
		while (queries[m].s > s) if (--cnt[A[s++]] == 0) --nowCnt; // ���� ���� Ȯ�� �� ���� ���
		// ���� �������� e�� ���� ��� ������ ���������κ��� ����ϸ� ��
		while (e > queries[m].e) if (--cnt[A[--e]] == 0) --nowCnt; // ���� ��� �� ���� Ȯ��
		// �̹� ������ ��� �ϼ�
		result[queries[m].n] = nowCnt;
	}

	for (int m{}; m < M; ++m) {
		cout << result[m] << '\n';
	}

	return 0;
}