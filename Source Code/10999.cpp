// lazy segment tree
// https://yabmoons.tistory.com/442 참고

#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;
using ll = long long;

struct Data_lazy {
	int s; // 시작 
	int e; // 끝
	long long lazy;
	Data_lazy(int s, int e, int l) : s(s), e(e), lazy(l) {}
};

vector<ll> tree;
vector<Data_lazy> lazy;
int leaf_count = 1;

void update_lazy(int index) {
	if (lazy[index].lazy!= 0) {
		// 구간만큼 값 갱신
		tree[index] += static_cast<ll>(lazy[index].e - lazy[index].s + 1) * lazy[index].lazy; 
		if (lazy[index].e != lazy[index].s) { 
			// 구간인 경우 자식에게 lazy value 상속
			lazy[index * 2].lazy += lazy[index].lazy;
			lazy[index * 2 + 1].lazy += lazy[index].lazy;
		}
		lazy[index].lazy = 0; // lazy value 반영 완료
	}
}

void update_range(int s, int e, ll value) {
	s = leaf_count + s - 1;
	e = leaf_count + e - 1;
	queue<tuple<int, int, int>> Q; // index, s, e
	Q.push(make_tuple(1, s, e));
	while (!Q.empty()) {
		auto now = Q.front();
		Q.pop();
		int now_index = get<0>(now);
		update_lazy(now_index);
		if (lazy[now_index].s == get<1>(now) && lazy[now_index].e == get<2>(now)) {
			// 더 이상 진행 x
			tree[now_index] += static_cast<ll>(lazy[now_index].e - lazy[now_index].s + 1) * value; // 구간만큼 값 갱신
			if (lazy[now_index].e != lazy[now_index].s) {
				// 구간인 경우 자식에게 lazy value 상속
				lazy[now_index * 2].lazy += value;
				lazy[now_index * 2 + 1].lazy += value;
			}
		}
		else {
			if (lazy[now_index * 2].e >= get<1>(now)) { // 왼쪽
				Q.push(make_tuple(now_index * 2, get<1>(now), min(lazy[now_index * 2].e, get<2>(now))));
				int interval = min(lazy[now_index * 2].e, get<2>(now)) - get<1>(now) + 1;
				tree[now_index] += static_cast<ll>(interval) * value; // 현재 tree 갱신
			}
			if (lazy[now_index * 2 + 1].s <= get<2>(now)) { // 오른쪽
				Q.push(make_tuple(now_index * 2 + 1, max(lazy[now_index * 2 + 1].s,get<1>(now)), get<2>(now)));
				int interval = get<2>(now) - max(lazy[now_index * 2 + 1].s, get<1>(now)) + 1;
				tree[now_index] += static_cast<ll>(interval) * value;
			}
		}
	}

}

ll cal_sum(int s, int e) { // top-down
	s = leaf_count + s - 1;
	e = leaf_count + e - 1;
	ll sum = 0;
	queue<tuple<int, int, int>> Q; // index, s, e
	Q.push(make_tuple(1, s, e));
	while (!Q.empty()) {
		auto now = Q.front();
		Q.pop();
		int now_index = get<0>(now);
		update_lazy(now_index);
		if (lazy[now_index].s == get<1>(now) && lazy[now_index].e == get<2>(now)) {
			sum += tree[now_index];
		}
		else {
			if (lazy[now_index * 2].e >= get<1>(now)) { // 왼쪽
				Q.push(make_tuple(now_index * 2, get<1>(now), min(lazy[now_index * 2].e, get<2>(now))));
			}
			if (lazy[now_index * 2 + 1].s <= get<2>(now)) { // 오른쪽
				Q.push(make_tuple(now_index * 2 + 1, max(lazy[now_index * 2 + 1].s, get<1>(now)), get<2>(now)));
			}
		}
	}

	return sum;
}

int main() {
	cin.tie(NULL)->sync_with_stdio(false);
	int N, M, K;
	cin >> N >> M >> K;

	while (leaf_count < N) {
		leaf_count <<= 1;
	}

	tree.assign(2 * leaf_count, 0);
	lazy.assign(2 * leaf_count, Data_lazy(0, 0, 0));
	for(int i=0;i<leaf_count;++i) {
		if (i < N) {
			cin >> tree[i + leaf_count];
		}
		lazy[i + leaf_count].s = lazy[i + leaf_count].e = i + leaf_count;
	}
	for (int i = leaf_count - 1; i >= 1; --i) {
		tree[i] = tree[i * 2] + tree[i * 2 + 1];
		lazy[i].s = lazy[i * 2].s;
		lazy[i].e = lazy[i * 2 + 1].e == 0 ? lazy[i*2].e : lazy[i*2 + 1].e;
	}

	int a, b, c;
	ll d;
	for (int i = 0; i < M + K; ++i) {
		cin >> a;
		if (a == 1) { // b ~ c에 d를 더하기
			cin >> b >> c >> d;
			// change_value(tree, b, c);
			update_range(b, c, d);
		}
		else { // b ~ c까지의 합
			cin >> b >> c;
			ll sum = 0;
			sum += cal_sum(b, c);
			cout << sum << '\n';
		}
	}

	return 0;
}
