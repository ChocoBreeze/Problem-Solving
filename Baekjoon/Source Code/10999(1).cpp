// lazy segment tree
// ���� �ڵ忡�� tuple �̻��

#include <iostream>
#include <vector>
#include <queue>

using namespace std;
using ll = long long;

struct Data_lazy {
	int s; // ���� 
	int e; // ��
	long long lazy;
	Data_lazy(int s, int e, int l) : s(s), e(e), lazy(l) {}
};

struct QData {
	int index, s, e;
	QData(int index, int s, int e) :index(index), s(s), e(e) {}
};

vector<ll> tree;
vector<Data_lazy> lazy;
int leaf_count = 1;

void update_lazy(int index) {
	if (lazy[index].lazy != 0) {
		// ������ŭ �� ����
		tree[index] += static_cast<ll>(lazy[index].e - lazy[index].s + 1) * lazy[index].lazy;
		if (lazy[index].e != lazy[index].s) {
			// ������ ��� �ڽĿ��� lazy value ���
			lazy[index * 2].lazy += lazy[index].lazy;
			lazy[index * 2 + 1].lazy += lazy[index].lazy;
		}
		lazy[index].lazy = 0; // lazy value �ݿ� �Ϸ�
	}
}

void update_range(int s, int e, ll value) {
	s = leaf_count + s - 1;
	e = leaf_count + e - 1;
	queue<QData> Q; // index, s, e
	Q.emplace(1, s, e);
	while (!Q.empty()) {
		QData now = Q.front(); Q.pop();
		int nowIndex{ now.index };
		int leftIndex{ nowIndex << 1 }, rightIndex{ (nowIndex << 1) + 1 };
		update_lazy(nowIndex);
		if (lazy[nowIndex].s == now.s && lazy[nowIndex].e == now.e) {
			// �� �̻� ���� x
			tree[nowIndex] += static_cast<ll>(lazy[nowIndex].e - lazy[nowIndex].s + 1) * value; // ������ŭ �� ����
			if (lazy[nowIndex].e != lazy[nowIndex].s) {
				// ������ ��� �ڽĿ��� lazy value ���
				lazy[leftIndex].lazy += value;
				lazy[rightIndex].lazy += value;
			}
		}
		else {
			if (lazy[leftIndex].e >= now.s) { // ����
				int left = nowIndex * 2;
				Q.emplace(leftIndex, now.s, min(lazy[leftIndex].e, now.e));
				int interval = min(lazy[leftIndex].e, now.e) - now.s + 1;
				tree[nowIndex] += static_cast<ll>(interval) * value; // ���� tree ����
			}
			if (lazy[rightIndex].s <= now.e) { // ������
				Q.emplace(rightIndex, max(lazy[rightIndex].s, now.s), now.e);
				int interval = now.e - max(lazy[rightIndex].s, now.s) + 1;
				tree[nowIndex] += static_cast<ll>(interval) * value;
			}
		}
	}

}

ll cal_sum(int s, int e) { // top-down
	s = leaf_count + s - 1;
	e = leaf_count + e - 1;
	ll sum = 0;
	queue<QData> Q; // index, s, e
	Q.emplace(1, s, e);
	while (!Q.empty()) {
		QData now = Q.front(); Q.pop();
		int nowIndex = now.index;
		int leftIndex{ nowIndex << 1 }, rightIndex{ (nowIndex << 1) + 1 };
		update_lazy(nowIndex);
		if (lazy[nowIndex].s == now.s && lazy[nowIndex].e == now.e) {
			sum += tree[nowIndex];
		}
		else {
			if (lazy[leftIndex].e >= now.s) { // ����
				Q.emplace(leftIndex, now.s, min(lazy[leftIndex].e, now.e));
			}
			if (lazy[rightIndex].s <= now.e) { // ������
				Q.emplace(rightIndex, max(lazy[rightIndex].s, now.s), now.e);
			}
		}
	}

	return sum;
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	int N, M, K;
	cin >> N >> M >> K; // ���� ����, ������ �Ͼ�� Ƚ��, ���� �� ���ϴ� Ƚ��

	while (leaf_count < N) {
		leaf_count <<= 1;
	}

	tree.assign(2 * leaf_count, 0);
	lazy.assign(2 * leaf_count, Data_lazy(0, 0, 0));
	for (int i = 0; i < leaf_count; ++i) {
		if (i < N) {
			cin >> tree[i + leaf_count];
		}
		lazy[i + leaf_count].s = lazy[i + leaf_count].e = i + leaf_count;
	}
	for (int i = leaf_count - 1; i >= 1; --i) {
		tree[i] = tree[i * 2] + tree[i * 2 + 1];
		lazy[i].s = lazy[i * 2].s;
		lazy[i].e = lazy[i * 2 + 1].e == 0 ? lazy[i * 2].e : lazy[i * 2 + 1].e;
	}

	int a, b, c;
	ll d;
	for (int i = 0; i < M + K; ++i) {
		cin >> a;
		if (a == 1) { // b ~ c�� d�� ���ϱ�
			cin >> b >> c >> d;
			// change_value(tree, b, c);
			update_range(b, c, d);
		}
		else { // b ~ c������ ��
			cin >> b >> c;
			ll sum = 0;
			sum += cal_sum(b, c);
			cout << sum << '\n';
		}
	}

	return 0;
}