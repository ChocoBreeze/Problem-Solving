// Persistent Segment Tree
// https://m.blog.naver.com/kks227/221411526404
// �ܿ� �����ߴ�..

// 2D ������ n���� ��ǥ. => ����� ������ ������� �ִ� ��.(��ǥ �ݺ� ����)
// ���� �ӱ� = m��.

// ������ ����� ��õ� ��� �׻� ��� ������ ���簢�� �������� ����.
// �۷��̵� ���� = [l, r] x [b, t]
// �۷��̵� ���� �ȿ� ���� ���� ���� ����
// x : [l, r], y : [b, t]

/*
Input
T : test case
n m : �ް� ������ ��� ��, �ӱ� �� ���� �� ��(=���� ��)
���� n�� -> (x, y)�� ��ġ�� ������ ��ǥ.
���� m�� -> �۷��̵� ����
Output
�� test case���� ���� ����� ����
*/

#include <iostream>
#include <cstring> // memset
#include <vector>
#include <algorithm>
#include <utility> // pair

using namespace std;

// ���� �Ҵ��� �������̰� ���쳪..
// �ӵ� ���鿡���� �̸� �� ����س��� ���� �Ҵ��� ����..

constinit const int MAX_DEPTH = 18; // ���׸�Ʈ Ʈ���� ���� - MAX_RANGE�� ���� ����.
constinit const int MAX_ST = 1 << MAX_DEPTH; // �ʱ�ȭ�� ���Ǵ� ��� ����(=0�� Ʈ���� ����� �� �ʿ��� ��� ����)
constinit const int MAX = 10001; // ���� ����
constinit const int MAX_RANGE = 100001; // ��ǥ���� ����
constinit const int MAX_NODE = MAX_ST + MAX * MAX_DEPTH; // ���� ��ü���� ���Ǵ� ��� ������ ����

// ���׸�Ʈ Ʈ�� ���
struct Node {
	int val; // �� : �� ��尡 �����ϴ� ���� ��
	int ns, ne; // �� ���� ���� [ns, ne)�� ��� �ִ�.
	int nNum; // �� ����� ��ȣ
	int lNum, rNum; // �� ����� ���� �ڽ�, ������ �ڽ� ����� ��ȣ
	Node() : Node(-1, -1, -1) {} // ns, ne, nNum
	Node(int ns, int ne, int nNum) : val(0), ns(ns), ne(ne), nNum(nNum), lNum(-1), rNum(-1) {}
};

struct PersistentSegTree {
	int TN; // ���� Ʈ���� ����
	int ncnt; // ���� ����� ���� : �� ����� ��ȣ�� ���� �� ���
	int root[MAX]; // root[k]: k��° Ʈ���� ��Ʈ ��� ��ȣ
	Node node[MAX_NODE];

	PersistentSegTree() : TN(0), ncnt(0) {
		memset(root, -1, sizeof(root)); // fill(root, root + MAX, -1);
		// 0�� Ʈ���� ����ִ� ��ȭ ���� Ʈ���� �����Ѵ�. ���� �׻� TN = 1�� ����
		root[TN++] = initialize(0, MAX_ST / 2);
	}

	// �ʱ�ȭ : ����ִ� ��ȭ ���� Ʈ�� ����.
	// ���� �׻� TN = 1�� ����.
	int initialize(int s, int e) {
		Node& curr = node[ncnt] = Node(s, e, ncnt);
		ncnt++;

		if (s + 1 < e) {
			int mid = s + (e - s) / 2;
			curr.lNum = initialize(s, mid);
			curr.rNum = initialize(mid, e);
		}
		return curr.nNum;
	}

	// �� Ʈ���� ����鼭 �ε��� y�� ���� ��忡 val��ŭ ����
	void addNode(int y, int val = 1) {
		// �� Ʈ���� ���� ��Ʈ ��� ��ȣ�� ����
		root[TN] = addNode(node[root[TN - 1]], y, val, 0, MAX_ST / 2);
		++TN;
	}
	int addNode(Node& shadow, int y, int val, int s, int e) {
		// ����� ������ y�� �������� ������ �� �ڸ��� ���� Ʈ�� ��带 ������(���� X)
		if (e <= y || y < s) return shadow.nNum;

		// ��带 �ϳ� ���� ����(���� O)
		Node& curr = node[ncnt] = Node(s, e, ncnt);
		ncnt++;

		if (s + 1 == e) { // ���� ���
			curr.val = shadow.val + val;
		}
		else { // ���ͳ� ��� (not leaf)
			int mid = s + (e - s) / 2;
			// left child
			curr.lNum = addNode(node[shadow.lNum], y, val, s, mid);
			// right child
			curr.rNum = addNode(node[shadow.rNum], y, val, mid, e);
			// �ڽ��� ���� ���� ����
			curr.val = node[curr.lNum].val + node[curr.rNum].val;

		}
		return curr.nNum; // �̹��� ���� ����� ��ȣ�� ����
	}

	// tn��° Ʈ���� ���� [s, e)�� ���� ����
	int sum(int tn, int s, int e) {
		return sum(node[root[tn]], s, e);
	}
	int sum(Node& curr, int s, int e) {
		if (e <= curr.ns || curr.ne <= s) return 0;
		if (s <= curr.ns && curr.ne <= e) return curr.val;
		return sum(node[curr.lNum], s, e) + sum(node[curr.rNum], s, e);
	}
};

using pii = pair<int, int>;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int T{}; cin >> T;
	
	int kk{};

	while (T--) {
		PersistentSegTree pst;
		int n, m; cin >> n >> m;
		vector<pii> eggs(n, make_pair(0,0));
		for (pii& egg : eggs) cin >> egg.first >> egg.second;
		sort(begin(eggs), end(eggs));
		vector<int> lastIndex(MAX_RANGE, 0); // lastIndex[x] : x��ǥ�� �����ϴ� ������ Ʈ�� �ε���
		// �ϴ� ������ġ�� �����ϰ�.. (���� ��(0)�� ���ؼ� �� ������ֱ�.. ���� ����� ä���)
		for (pii& egg : eggs) {
			auto& [x, y] = egg;
			pst.addNode(y);
			lastIndex[x] = pst.TN - 1; // �̹��� ���� ��尡 ��ġ�� Ʈ���� ��Ʈ �ε���
		}
		int lastValue{};
		for (int& lasti : lastIndex) {
			if (lasti != lastValue) {
				if (lasti > lastValue) { // �ٸ� lasti value
					lastValue = lasti;
				}
				else { // lasti == 0
					lasti = lastValue;
				}
			}
		}
		int answer{};
		for (int q{}; q < m; ++q) {
			int l{}, r{}, b{}, t{};
			cin >> l >> r >> b >> t;
			answer += pst.sum(lastIndex[r], b, t + 1);
			if (l > 0) answer -= pst.sum(lastIndex[l - 1], b, t + 1);
		}
		cout << answer << '\n';
	}

	return 0;
}