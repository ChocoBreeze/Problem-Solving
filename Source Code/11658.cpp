// 세그먼트 트리 구조 참고
// https://m.blog.naver.com/PostView.naver?isHttpsRedirect=true&blogId=jh20s&logNo=221351546136
#include <iostream>
#include <vector>

using namespace std;

int tmp_N = 1;
// 1024 * 1024 * 1000 = 1,048,576,000

void make_tree_y(vector<vector<int>>& seg_tree, int i, int j) {
	while (j > 1) { // 기존 1차원 트리
		int parent = j >> 1;
		seg_tree[i][parent] = seg_tree[i][parent * 2] + seg_tree[i][parent * 2 + 1];
		j = parent;
	}
}

void update(vector<vector<int>>& seg_tree, int i, int j) {
	i += tmp_N;
	j += tmp_N;
	make_tree_y(seg_tree, i, j);
	while (i > 1) {
		int parent_i = i >> 1;
		seg_tree[parent_i][j] = seg_tree[parent_i * 2][j] + seg_tree[parent_i * 2 + 1][j];
		make_tree_y(seg_tree, parent_i, j);
		i = parent_i;
	}
}

int get_sum_y(vector<vector<int>>& seg_tree, int x, int y1, int y2) {
	y1 += tmp_N;
	y2 += tmp_N;
	int sum = 0;
	while (y1 <= y2) {
		if ((y1 & 1) == 1) sum += seg_tree[x][y1];
		if ((y2 & 1) == 0) sum += seg_tree[x][y2];

		y1 = (y1 + 1) >> 1;
		y2 = (y2 - 1) >> 1;
	}
	return sum;
}

int get_sum(vector<vector<int>>& seg_tree, int x1, int y1, int x2, int y2) {
	// x 범위
	int sum = 0;
	x1 += tmp_N;
	x2 += tmp_N;
	while (x1 <= x2) {
		if ((x1 & 1) == 1) sum += get_sum_y(seg_tree, x1, y1, y2);
		if ((x2 & 1) == 0) sum += get_sum_y(seg_tree, x2, y1, y2);

		x1 = (x1 + 1) >> 1;
		x2 = (x2 - 1) >> 1;
	}

	return sum;
}

int main() {
	cin.tie(NULL)->sync_with_stdio(false);
	int N, M, w;
	cin >> N >> M;
	while (tmp_N < N) {
		tmp_N <<= 1;
	}

	vector<vector<int>> seg_tree(tmp_N * 2, vector<int>(tmp_N * 2, 0));

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			cin >> seg_tree[i + tmp_N][j + tmp_N];
			update(seg_tree, i, j);
		}
	}

	for (int i = 0; i < M; ++i) {
		cin >> w;
		if (w == 0) { // (x, y) -> c
			int x, y, c;
			cin >> x >> y >> c;
			x--; y--;
			seg_tree[x + tmp_N][y + tmp_N] = c;
			update(seg_tree, x, y);
		}
		else { // (x1, y1) ~ (x2, y2) 합
			int x1, y1, x2, y2;
			cin >> x1 >> y1 >> x2 >> y2;
			x1--; y1--; x2--; y2--;
			if (x1 > x2) swap(x1, x2);
			if (y1 > y2) swap(y1, y2);
			cout << get_sum(seg_tree, x1,y1,x2,y2) << '\n';
		}
	}

	return 0;
}