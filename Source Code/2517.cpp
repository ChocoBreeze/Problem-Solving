#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> tree;

struct Data {
	int p;
	int index;
	Data(int p, int i) : p(p), index(i) {}
};

auto compare = [](Data& a, Data& b) {
	return a.p < b.p; // ascend
};

int get_sum(int leaf_start, int s, int e) {
	int sum = 0;
	s = leaf_start + s;
	e = leaf_start + e;
	while (s <= e) {
		if ((s & 1) == 1) sum += tree[s]; // % 대신 bit 연산
		if ((e & 1) == 0) sum += tree[e];
		s = (s + 1) >> 1;
		e = (e - 1) >> 1;
	}
	return sum;
}

void update(int leaf_start, int index, int value) {
	index = leaf_start + index;
	tree[index] = value;
	while (index > 1) {
		index >>= 1;
		tree[index] = tree[index * 2] + tree[index * 2 + 1];
	}
}

int main() {
	int N, e;
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	cin >> N;
	vector<Data> A(N, Data(0,0)), A_(N, Data(0, 0));
	for (int i = 0; i < N;++i) {
		cin >> A[i].p;
		A[i].index = i;
		A_[i] = A[i];
	}
	A_.assign(begin(A), end(A));
	// index를 위해 정렬(그냥 실력으로 정렬하면 10억이라 메모리 초과)
	sort(begin(A_), end(A_),compare);
	for (int i = 0; i < N; ++i) {
		A[A_[i].index].index = i;
	}

	int tmpN = 1; // N : 1 ~ 500000
	while (tmpN < N) { // N = 5 - tmpN = 8
		tmpN <<= 1;
	}
	tree.assign(tmpN * 2, 0);
	for(int n=0;n<N;++n) {
		cout << n - get_sum(tmpN, 0, A[n].index) + 1 << "\n";
		update(tmpN, A[n].index, 1);
	}

	return 0;
}