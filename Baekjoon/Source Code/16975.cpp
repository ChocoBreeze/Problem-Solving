// SegTree, Lazy Propagation
// 6128KB, 92ms
#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

struct SegTree {
	vector<ll> lazy; // lazy
	vector<ll> elem; // 원소의 합
	int leafS, N;
	SegTree(int N) : N(N) {
		leafS = 1;
		while (leafS < N) leafS <<= 1;
		leafS <<= 1;
		elem = vector<ll>(leafS, 0);
		lazy = vector<ll>(leafS, 0);
		leafS >>= 1;
	}

	void Init() {
		for (int i{ leafS }; i < leafS + N; ++i) {
			cin >> elem[i];
		}
		for (int i{ leafS - 1 }; i > 0; --i) {
			elem[i] = elem[i * 2] + elem[i * 2 + 1];
		}
	}

	// 구간 [ns, ne)
	void Propagate(int node, int ns, int ne) {
		if (lazy[node] != 0) {
			if (node < leafS) { // 리프노드가 아닌 경우 자식에게 lazy 전파
				lazy[node * 2] += lazy[node];
				lazy[node * 2 + 1] += lazy[node];
			}
			elem[node] += lazy[node] * (ne - ns);
			lazy[node] = 0;
		}
	}

	// 구간 [s, e)에 k 더하기 - 구간 시작 = 0
	void Add(int s, int e, int k) { Add(s, e, k, 1, 0, leafS); }
	void Add(int s, int e, int k, int node, int ns, int ne) {
		Propagate(node, ns, ne);

		if (e <= ns || ne <= s) return; // 해당 구간 X
		if (s <= ns && ne <= e) { // 완전히 포함되는 구간
			lazy[node] += k;
			Propagate(node, ns, ne);
			return;
		}
		int mid = ns + (ne - ns) / 2;
		Add(s, e, k, node * 2, ns, mid);
		Add(s, e, k, node * 2 + 1, mid, ne);
		elem[node] = elem[node * 2] + elem[node * 2 + 1];
	}

	// 구간 [s, e)의 합 구하기
	long long sum(int s, int e) { return sum(s, e, 1, 0, leafS); }
	long long sum(int s, int e, int node, int ns, int ne) {
		// 일단 propagate
		Propagate(node, ns, ne);

		if (e <= ns || ne <= s) return 0; // 맞는 범위가 아님
		if (s <= ns && ne <= e) return elem[node]; // 정확히 포함되는 구간

		int mid = ns + (ne - ns) / 2;
		return sum(s, e, node * 2, ns, mid) + sum(s, e, node * 2 + 1, mid, ne);
	}

};

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int N{}; cin >> N;
	SegTree st(N);
	st.Init();

	int M{}; cin >> M;
	for (int m{}; m < M; ++m) {
		int op{}; cin >> op;
		if (op == 1) { // 1 i j k => A_i ... A_j에 k를 더하기
			int i{}, j{}, k{}; cin >> i >> j >> k; // 
			// 원하는 구간 : [i, j] (1부터 시작) => [i - 1, j) (0부터 시작)
			st.Add(i-1,j, k);
		}
		else { // 2 x => A_x를 출력하기.
			int x{}; cin >> x; // x (1부터 시작) => [x-1, x) (0부터 시작)
			cout << st.sum(x - 1,x) << '\n';
		}
	}

	return 0;
}