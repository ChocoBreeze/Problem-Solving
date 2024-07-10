// Segment Tree With Lazy Propagation
// https://book.acmicpc.net/ds/segment-tree-lazy-propagation
// https://www.acmicpc.net/problem/10999
// 42616KB, 208ms

#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

void InitTree(vector<ll>& a, vector<ll>& tree, int node, int start, int end) {
	if (start == end) { // leaf
		tree[node] = a[start];
	}
	else {
		int mid = start + (end - start) / 2;
		InitTree(a, tree, node * 2, start, mid);
		InitTree(a, tree, node * 2 + 1, mid + 1, end);
		tree[node] = tree[node * 2] + tree[node * 2 + 1];
	}
}
void UpdateLazy(vector<long long>& tree, vector<long long>& lazy, int node, int start, int end) {
	if (lazy[node] != 0) {
		tree[node] += (end - start + 1) * lazy[node]; // 구간 * lazy
		if (start != end) {
			lazy[node * 2] += lazy[node];
			lazy[node * 2 + 1] += lazy[node];
		}
		lazy[node] = 0;
	}
}
void UpdateRange(vector<long long>& tree, vector<long long>& lazy, int node, int start, int end, int left, int right, long long diff) {
	UpdateLazy(tree, lazy, node, start, end);
	if (left > end || right < start) {
		return;
	}
	if (left <= start && end <= right) {
		tree[node] += (end - start + 1) * diff;
		if (start != end) {
			lazy[node * 2] += diff;
			lazy[node * 2 + 1] += diff;
		}
		return;
	}
	int mid = start + (end - start) / 2;
	UpdateRange(tree, lazy, node * 2, start, mid, left, right, diff);
	UpdateRange(tree, lazy, node * 2 + 1, mid + 1, end, left, right, diff);
	tree[node] = tree[node * 2] + tree[node * 2 + 1];
}
ll Sum(vector<long long>& tree, vector<long long>& lazy, int node, int start, int end, int left, int right) {
	UpdateLazy(tree, lazy, node, start, end);
	if (left > end || right < start) { // 구간 밖
		return 0;
	}
	if (left <= start && end <= right) { // 완전히 포함되는 구간
		return tree[node];
	}
	int mid = start + (end - start) / 2;
	ll lsum = Sum(tree, lazy, node * 2, start, mid, left, right);
	ll rsum = Sum(tree, lazy, node * 2 + 1, mid + 1, end, left, right);
	return lsum + rsum;
}


int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int N{}, M{}, K{}; cin >> N >> M >> K;
	vector<ll> a(N, 0);
	for (ll& i : a) cin >> i;

	int treeSize{ 1 };
	while (treeSize < N) treeSize <<= 1;
	treeSize <<= 1;
	vector<ll> tree(treeSize, 0), lazy(treeSize, 0);

	InitTree(a, tree, 1, 0, N - 1);
	for (int i{}; i < M + K; ++i) {
		int a{}, b{}, c{}; ll d{};
		cin >> a;
		if (a == 1) { // b번째 수부터 c번째 수에 d를 더하기
			cin >> b >> c >> d;
			UpdateRange(tree, lazy, 1, 0, N - 1, b - 1, c - 1, d);
		}
		else { // b번째 수부터 c번째 수의 합
			cin >> b >> c;
			cout << Sum(tree, lazy, 1, 0, N-1, b - 1, c - 1) << '\n';
		}
	}

	return 0;
}