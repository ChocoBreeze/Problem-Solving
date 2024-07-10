// Square Root Decomposition, Mo's Algorithm
// https://m.blog.naver.com/kks227/221401154455

#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;
using ll = long long;

/*
��� ���� Q = (s, e)�� ����,?([s/��N], e) ������ �������� ����
������ ���� ��� �ٷ� ���� ������ ����� ����
*/

int sqrtN;
// ���� ������ ���� ���� ����ü
struct QueryNode {
	int s, e, n; // n�� ���� ��ȣ
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

	// ù ��°�� ��ġ�� ������ ����� �ռ� ����
	ll sum{};
	vector<ll> result(M, 0);
	auto& [s, e, n] = queries[0];
	for (int i{ s }; i < e; ++i) {
		sum += vec[i];
	}
	result[n] = sum;

	// ���� ��������, �ٷ� ���� ������ ����� ����� ���!
	for (int i{ 1 }; i < M; ++i) {
		// ���� �������� s�� ���� ��� �������� ������ Ȯ���ϸ� ����
		while (queries[i].s < s) sum += vec[--s];
		// ���� �������� e�� Ŭ ��� ���������� ������ Ȯ���ϸ� ����
		while (e < queries[i].e) sum += vec[e++];
		// ���� �������� s�� Ŭ ��� ������ �������κ��� ����ϸ� ��
		while (queries[i].s > s) sum -= vec[s++];
		// ���� �������� e�� ���� ��� ������ ���������κ��� ����ϸ� ��
		while (e > queries[i].e) sum -= vec[--e];
		// �̹� ������ ��� �ϼ�
		result[queries[i].n] = sum;
	}

	// ���� ����� �� ���� ó��
	for (int m{}; m < M; ++m) {
		cout << result[m] << '\n';
	}

	return 0;
}