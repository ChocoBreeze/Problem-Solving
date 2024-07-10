// 기존 코드 업데이트
// https://yabmoons.tistory.com/442 - 아이디어
// Structured Binding 사용 + tuple 제거

#include <iostream>
#include <vector>
#include <queue>

using namespace std;
using ll = long long;

struct Data_lazy
{
	int s, e;
	ll lazy;
	Data_lazy(int s, int e, ll l) : s(s), e(e), lazy(l) {}
};

struct QData
{
	int index, s, e;
	QData(int index, int s, int e) : index(index), s(s), e(e) {}
};

vector<ll> tree;
vector<Data_lazy> lazy;
int leaf_count{1};

void update_lazy(int index)
{
	if (lazy[index].lazy != 0)
	{
		tree[index] += static_cast<ll>(lazy[index].e - lazy[index].s + 1) * lazy[index].lazy; // 구간만큼 값 갱신
		if (lazy[index].e != lazy[index].s)
		{ // 구간인 경우 자식에게 lazy value 상속
			lazy[index * 2].lazy += lazy[index].lazy;
			lazy[index * 2 + 1].lazy += lazy[index].lazy;
		}
		lazy[index].lazy = 0; // lazy value 반영 완료
	}
}

void update_range(int s, int e, ll value)
{
	s += leaf_count - 1;
	e += leaf_count - 1;
	queue<QData> Q; // index, s, e
	Q.push(QData(1, s, e));
	while (!Q.empty())
	{
		auto [now_index, now_s, now_e] = Q.front();
		Q.pop();
		update_lazy(now_index); // 기존 lazy 값 갱신
		if (lazy[now_index].s == now_s && lazy[now_index].e == now_e)
		{
			// 더 이상 진행 x
			tree[now_index] += static_cast<ll>(lazy[now_index].e - lazy[now_index].s + 1) * value; // 구간만큼 값 갱신
			if (lazy[now_index].e != lazy[now_index].s)
			{
				// 구간인 경우 자식에게 lazy value 상속
				lazy[now_index * 2].lazy += value;
				lazy[now_index * 2 + 1].lazy += value;
			}
		}
		else
		{ // 구간인 경우
			if (lazy[now_index * 2].e >= now_s)
			{ // 왼쪽
				Q.push(QData(now_index * 2, now_s, min(lazy[now_index * 2].e, now_e)));
				int interval = min(lazy[now_index * 2].e, now_e) - now_s + 1;
				tree[now_index] += static_cast<ll>(interval) * value; // 현재 tree 갱신
			}
			if (lazy[now_index * 2 + 1].s <= now_e)
			{ // 오른쪽
				Q.push(QData(now_index * 2 + 1, max(lazy[now_index * 2 + 1].s, now_s), now_e));
				int interval = now_e - max(lazy[now_index * 2 + 1].s, now_s) + 1;
				tree[now_index] += static_cast<ll>(interval) * value;
			}
		}
	}
}

ll cal_sum(int s, int e)
{ // top-down
	s += leaf_count - 1;
	e += leaf_count - 1;
	ll sum = 0;
	queue<QData> Q; // index, s, e
	Q.push(QData(1, s, e));
	while (!Q.empty())
	{
		auto [now_index, now_s, now_e] = Q.front();
		Q.pop();
		update_lazy(now_index); // 기존 lazy 갱신
		if (lazy[now_index].s == now_s && lazy[now_index].e == now_e)
		{
			sum += tree[now_index]; // 같은 값인 경우 합 계산
		}
		else
		{ // 구간인 경우
			if (lazy[now_index * 2].e >= now_s)
			{ // 왼쪽
				Q.push(QData(now_index * 2, now_s, min(lazy[now_index * 2].e, now_e)));
			}
			if (lazy[now_index * 2 + 1].s <= now_e)
			{ // 오른쪽
				Q.push(QData(now_index * 2 + 1, max(lazy[now_index * 2 + 1].s, now_s), now_e));
			}
		}
	}
	return sum;
}

int main()
{
	cin.tie(NULL)->sync_with_stdio(false);
	int N, M, K;
	cin >> N >> M >> K;

	while (leaf_count < N)
	{
		leaf_count <<= 1;
	}

	leaf_count <<= 1;
	tree.assign(leaf_count, 0);
	lazy.assign(leaf_count, Data_lazy(0, 0, 0));
	leaf_count >>= 1;

	// make leaf node
	for (int i = 0; i < leaf_count; ++i)
	{
		int idx = i + leaf_count;
		if (i < N)
		{
			cin >> tree[idx];
		}
		lazy[idx].s = lazy[idx].e = idx;
	}

	// make tree (not leaf node)
	for (int i = leaf_count - 1; i >= 1; --i)
	{
		int leftChild{i * 2}, rightChild{i * 2 + 1};
		tree[i] = tree[leftChild] + tree[rightChild];
		lazy[i].s = lazy[leftChild].s;
		lazy[i].e = lazy[rightChild].e == 0 ? lazy[leftChild].e : lazy[rightChild].e; // 굳이 했어야 했나?
	}

	int a, b, c;
	ll d;
	for (int i = 0; i < M + K; ++i)
	{
		cin >> a;
		if (a == 1)
		{ // b ~ c에 d를 더하기
			cin >> b >> c >> d;
			update_range(b, c, d);
		}
		else
		{ // b ~ c까지의 합
			cin >> b >> c;
			cout << cal_sum(b, c) << '\n';
		}
	}

	return 0;
}