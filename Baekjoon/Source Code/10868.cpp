// index tree
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
const int MAX = 1000000000;

void make_tree(vector<int>& index_tree, int index) {
	while (index > 1) {
		int parent = index >> 1;
		index_tree[parent] = min(index_tree[parent * 2], index_tree[parent * 2 + 1]);
		index = parent;
	}
}

int get_min(vector<int>& index_tree, int a, int b) {
	int answer = MAX;
	while (a <= b) {
		if (a % 2 == 1) answer = min(answer, index_tree[a]);
		if (b % 2 == 0) answer = min(answer, index_tree[b]);
		a = (a + 1) >> 1;
		b = (b - 1) >> 1;
	}
	return answer;
}

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	int N, M, a, b;
	cin >> N >> M;
	int leaf_size = 1;
	for (; leaf_size < N; leaf_size <<= 1);
	vector<int> index_tree(leaf_size * 2, MAX);
	for (int n = 0; n < N; ++n) {
		cin >> index_tree[leaf_size + n];
		make_tree(index_tree, leaf_size + n);
	}
	for (int m = 0; m < M; ++m) {
		cin >> a >> b;
		a = leaf_size + a - 1;
		b = leaf_size + b - 1;
		cout << get_min(index_tree, a, b) << "\n";
	}
	return 0;
}