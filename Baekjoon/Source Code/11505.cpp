#include <iostream>
#include <vector>

using namespace std;

void set_tree(vector<long long>& i_tree, int index) {
	while (index > 1) {
		int parent = index >> 1;
		i_tree[parent] = i_tree[parent * 2] * i_tree[parent * 2 + 1];
		i_tree[parent] %= 1000000007;
		index = parent;
	}
}

long long cal_mul(vector<long long>& i_tree, int b, int c) {
	long long answer = 1;
	while (b <= c) {
		if ((b & 1) == 1) {
			answer *= i_tree[b];
			answer %= 1000000007;
		}
		if ((c & 1) == 0) {
			answer *= i_tree[c];
			answer %= 1000000007;
		}
		b = (b + 1) >> 1;
		c = (c - 1) >> 1;
	}
	return answer;
}

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	int N, M, K;
	cin >> N >> M >> K;
	int leaf = 1;
	while (leaf < N) {
		leaf <<= 1;
	}
	vector<long long> i_tree(2 * leaf, 1); // 곱
	for (int i = 0; i < N; ++i) {
		cin >> i_tree[leaf + i];
		set_tree(i_tree, leaf + i);
	}

	int a, b, c;
	for (int n = 0; n < M + K; ++n) {
		cin >> a >> b >> c;
		if (a == 1) { // b번째 수를 c로 변경
			b = leaf + b - 1;
			i_tree[b] = c;
			set_tree(i_tree, b);
		}
		else { // b부터 c까지 곱
			b = leaf + b - 1;
			c = leaf + c - 1;
			cout << cal_mul(i_tree, b, c) << "\n";
		}
	}

	return 0;
}