// index tree(segment tree)
// 신기하다!
#include <iostream>
#include <vector>

using namespace std;

vector<long long> tree;

void set_tree(int start_index) {
	for (int i = start_index - 1; i >= 1; --i) {
		tree[i] = tree[i * 2] + tree[i * 2 + 1];
	}
}

void change_value(int start_index, long long index, long long value) {
	index = index + start_index - 1;
	tree[index] = value;
	while (index > 1) {
		index >>= 1;
		tree[index] = tree[index * 2] + tree[index * 2 + 1];
	}
}

long long cal_sum(int start_index, long long s, long long e) {
	long long sum = 0;
	s = start_index + s - 1;
	e = start_index + e - 1;
	// 짝수 = left_child, 홀수 = right_child
	while (s <= e) {
		if ((s & 1) == 1) sum += tree[s]; // s가 right_child일 때
		// s가 right_child이면 parent로 가도 구간합에 필요한 정보가 없음.
		if ((e & 1) == 0) sum += tree[e]; // e가 left_child일 때
		// e가 left_child이면 parent로 가도 구간합에 필요한 정보가 없음.
		
		s = (s + 1) >> 1; // a는 right parent로 이동
		// s가 left_child이면 그냥 자신의 부모로 올라감.
		e = (e - 1) >> 1; // e는 left parent로 이동
		// e가 right child이면 그냥 자신의 부모로 올라감.
	}
	return sum;
}

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	int N, M, K;
	// N = 수의 개수 | M = 변경 횟수 | K = 구간의 합 구하는 횟수
	cin >> N >> M >> K;
	int tmpN = 1; // N : 1 ~ 1000000
	while (tmpN < N) { // N = 5 - tmpN = 8
		tmpN <<= 1;
	}
	
	tree.assign(tmpN * 2, 0);
	for (int n = 0; n < N; ++n) {
		cin >> tree[tmpN + n];
	}
	set_tree(tmpN);

	long long a, b, c;
	for (int i = 0; i < M + K; ++i) {
		cin >> a >> b >> c;
		if (a == 1) { // change b번째 수를 c로 change
			change_value(tmpN, b, c);
		}
		else { // a == 2 : b ~ c까지 구간 합
			cout << cal_sum(tmpN, b, c) << "\n";
		}
	}
	return 0;
}