// index tree
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct min_max {
	int mini;
	int maxi;
	min_max(int mini, int maxi) : mini(mini), maxi(maxi) {}
};

const int MAX = 1000000010;

void init_tree(vector<min_max>& i_tree, int index) {
	while (index > 1) {
		int parent = index >> 1;
		int c1 = parent * 2, c2 = parent * 2 + 1;
		i_tree[parent].mini = min(i_tree[c1].mini, i_tree[c2].mini);
		i_tree[parent].maxi = max(i_tree[c1].maxi, i_tree[c2].maxi);
		index = parent;
	}
}

min_max find_answer(vector<min_max>& i_tree, int a, int b) {
	min_max answer = min_max(MAX, 0);
	while (a <= b) {
		answer.maxi = max(answer.maxi, i_tree[a].maxi);
		answer.maxi = max(answer.maxi, i_tree[b].maxi);
		answer.mini = min(answer.mini, i_tree[a].mini);
		answer.mini = min(answer.mini, i_tree[b].mini);
		
		a = (a + 1) >> 1;
		b = (b - 1) >> 1;
	}
	return answer;
}

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	int N, M; 
	cin >> N >> M; // N : 숫자 개수 -> index tree leaf node
	int leaf=0;
	for (int i = 1;; i<<=1) {
		leaf = i;
		if (i > N) break;
	}
	vector<min_max> i_tree(2 * leaf, min_max(MAX,0));

	for (int l = leaf; l < leaf + N; ++l) {
		int temp;
		cin >> temp;
		i_tree[l].mini = temp;
		i_tree[l].maxi = temp;
		init_tree(i_tree, l);
	}
	int a, b;
	for (int m = 0; m < M; ++m) {
		cin >> a >> b;
		a += leaf - 1;
		b += leaf - 1;
		min_max answer = find_answer(i_tree, a, b);
		cout << answer.mini << " " << answer.maxi << "\n";
	}
	return 0;
}