// Persistent Segment Tree
// https://m.blog.naver.com/kks227/221411526404
// 겨우 이해했다..

// 2D 지도에 n개의 좌표. => 계란을 던지는 사람들이 있는 곳.(좌표 반복 가능)
// 남은 임기 = m일.

// 행진은 헌법에 명시된 대로 항상 축과 평행한 직사각형 영역에서 열림.
// 퍼레이드 범위 = [l, r] x [b, t]
// 퍼레이드 범위 안에 속한 점의 개수 세기
// x : [l, r], y : [b, t]

/*
Input
T : test case
n m : 달걀 던지는 사람 수, 임기 내 남은 일 수(=쿼리 수)
다음 n개 -> (x, y)에 위치한 집들의 좌표.
다음 m개 -> 퍼레이드 범위
Output
각 test case마다 받은 계란의 개수
*/

#include <iostream>
#include <cstring> // memset
#include <vector>
#include <algorithm>
#include <utility> // pair

using namespace std;

// 동적 할당이 직관적이고 쉬우나..
// 속도 측면에서는 미리 다 계산해놓는 정적 할당이 빠름..

constinit const int MAX_DEPTH = 18; // 세그먼트 트리의 높이 - MAX_RANGE와 관련 있음.
constinit const int MAX_ST = 1 << MAX_DEPTH; // 초기화에 사용되는 노드 개수(=0번 트리를 만드는 데 필요한 노드 개수)
constinit const int MAX = 10001; // 점의 개수
constinit const int MAX_RANGE = 100001; // 좌표값의 범위
constinit const int MAX_NODE = MAX_ST + MAX * MAX_DEPTH; // 문제 전체에서 사용되는 노드 개수의 상한

// 세그먼트 트리 노드
struct Node {
	int val; // 값 : 이 노드가 포함하는 구간 합
	int ns, ne; // 이 노드는 구간 [ns, ne)를 담고 있다.
	int nNum; // 이 노드의 번호
	int lNum, rNum; // 이 노드의 왼쪽 자식, 오른쪽 자식 노드의 번호
	Node() : Node(-1, -1, -1) {} // ns, ne, nNum
	Node(int ns, int ne, int nNum) : val(0), ns(ns), ne(ne), nNum(nNum), lNum(-1), rNum(-1) {}
};

struct PersistentSegTree {
	int TN; // 현재 트리의 개수
	int ncnt; // 현재 노드의 개수 : 새 노드의 번호를 붙일 때 사용
	int root[MAX]; // root[k]: k번째 트리의 루트 노드 번호
	Node node[MAX_NODE];

	PersistentSegTree() : TN(0), ncnt(0) {
		memset(root, -1, sizeof(root)); // fill(root, root + MAX, -1);
		// 0번 트리를 비어있는 포화 이진 트리로 구축한다. 따라서 항상 TN = 1로 시작
		root[TN++] = initialize(0, MAX_ST / 2);
	}

	// 초기화 : 비어있는 포화 이진 트리 구축.
	// 따라서 항상 TN = 1로 시작.
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

	// 새 트리를 만들면서 인덱스 y인 리프 노드에 val만큼 더함
	void addNode(int y, int val = 1) {
		// 새 트리를 만들어서 루트 노드 번호를 저장
		root[TN] = addNode(node[root[TN - 1]], y, val, 0, MAX_ST / 2);
		++TN;
	}
	int addNode(Node& shadow, int y, int val, int s, int e) {
		// 노드의 구간이 y를 포함하지 않으면 이 자리의 이전 트리 노드를 돌려줌(갱신 X)
		if (e <= y || y < s) return shadow.nNum;

		// 노드를 하나 새로 만듦(갱신 O)
		Node& curr = node[ncnt] = Node(s, e, ncnt);
		ncnt++;

		if (s + 1 == e) { // 리프 노드
			curr.val = shadow.val + val;
		}
		else { // 인터널 노드 (not leaf)
			int mid = s + (e - s) / 2;
			// left child
			curr.lNum = addNode(node[shadow.lNum], y, val, s, mid);
			// right child
			curr.rNum = addNode(node[shadow.rNum], y, val, mid, e);
			// 자신의 구간 합을 구함
			curr.val = node[curr.lNum].val + node[curr.rNum].val;

		}
		return curr.nNum; // 이번에 만든 노드의 번호를 리턴
	}

	// tn번째 트리의 구간 [s, e)의 합을 구함
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
		vector<int> lastIndex(MAX_RANGE, 0); // lastIndex[x] : x좌표가 등장하는 마지막 트리 인덱스
		// 일단 등장위치만 저장하고.. (없는 값(0)에 대해서 다 만들어주기.. 이전 값들로 채우기)
		for (pii& egg : eggs) {
			auto& [x, y] = egg;
			pst.addNode(y);
			lastIndex[x] = pst.TN - 1; // 이번에 넣은 노드가 위치한 트리의 루트 인덱스
		}
		int lastValue{};
		for (int& lasti : lastIndex) {
			if (lasti != lastValue) {
				if (lasti > lastValue) { // 다른 lasti value
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