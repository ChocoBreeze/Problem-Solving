#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using pii = pair<int, int>; // query 1
using ll = long long;

struct Query { // query 2
	int index; // 답으로 사용할 index
	int k, i, j; // kth query 수행
	bool operator<(const Query& other) const {
		return k < other.k; // k로 정렬
	}
	Query(int index, int k, int i, int j) : index(index), k(k), i(i), j(j) {}
};

struct SegTree {
	int rootS;
	vector<ll> elem; // 당연히 여기도 ll
	
	SegTree(int N) {
		rootS = 1;
		while (rootS < N) rootS <<= 1;
		rootS <<= 1;
		elem.assign(rootS, 0LL);
		rootS >>= 1;
	}

	void MakeLeaf(int N) {
		for (int n{}; n < N; ++n) {
			cin >> elem[rootS + n];
		}
	}

	void MakeInitialTree() {
		for (int n{ rootS - 1 }; n >= 1; --n) {
			elem[n] = elem[n * 2] + elem[n * 2 + 1];
		}
	}

	void SetValue(int i, int v) { // ith value => v
		i += rootS - 1;
		elem[i] = v;
		while (i) {
			int par = i >> 1;
			elem[par] = elem[par * 2] + elem[par * 2 + 1];
			i = par;
		}
	}

	ll Query(int i, int j) { // [i, j] 구간 합
		ll ret{};
		i += rootS - 1, j += rootS - 1;
		while (i <= j) {
			if (i & 1) ret += elem[i];
			if (!(j & 1)) ret += elem[j];
			i = (i + 1) >> 1;
			j = (j - 1) >> 1;
		}
		return ret;
	}
};

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int N{}; cin >> N;

	SegTree st(N);
	st.MakeLeaf(N);
	st.MakeInitialTree();
	
	int M{}; cin >> M;
	vector<pii> q1; q1.reserve(M); q1.emplace_back(0, 0);
	vector<Query> q2; q2.reserve(M);
	for (int m{}; m < M; ++m) {
		int op{}; cin >> op;
		if (op == 1) {
			int i, v; cin >> i >> v;
			q1.emplace_back(i, v);
		}
		else { // (op == 2)
			int k, i, j; cin >> k >> i >> j;
			int index = static_cast<int>(q2.size());
			q2.emplace_back(index, k, i, j);
		}
	}
	vector<ll> answer(q2.size(), 0LL);
	sort(begin(q2), end(q2)); // k순 오름차순 정렬

	int q2Index{};
	for (int q{}; q < static_cast<int>(q1.size()); ++q) {
		if (q) { // qth q1 query 수행
			auto& [i, v] = q1[q];
			st.SetValue(i, v);
		}
		for(; q2Index < static_cast<int>(q2.size()) && q2[q2Index].k <= q; ++q2Index) {
			auto& [index, k, i, j] = q2[q2Index];
			answer[index] = st.Query(i, j);
		}
	}

	for (auto& a : answer) cout << a << '\n';
	return 0;
}