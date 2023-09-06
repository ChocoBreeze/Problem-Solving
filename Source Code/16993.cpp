// 참고) 금광 세그.. 
// https://viyoung.tistory.com/149
// https://blog.naver.com/jinhan814/222172647341
// https://seungwuk98.tistory.com/39
// https://blog.naver.com/melon940925/222135733526
// 분할 정복 + segment Tree
// 6512KB, 88ms

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>  // INT_MIN

using namespace std;
constinit const int INF = -123456789;

/**
* left : [left, ~]의 최대 연속합. -> 갱신 = max(왼쪽 자식 노드의 왼쪽(left), 왼쪽 자식 노드 전체합(sum) + 오른쪽 자식 노드의 왼쪽(left))
* right : [~, right]의 최대 연속합. -> 갱신 = max(오른쪽 자식 노드의 오른쪽(right), 왼쪽 자식 노드의 오른쪽(right) + 오른쪽 자식 노드의 전체합(sum))
* max : [left, right]에서의 최대 값. -> max(왼쪽 자식 노드의 최대값(max), 오른쪽 자식 노드의 최대값(max), 왼쪽 자식 노드의 오른쪽(right) + 오른쪽 자식 노드의 왼쪽(left))
* sum : [left, right]의 구간합.
*/
struct Node {
	int left, right, max, sum;
	Node(int l, int r, int m, int s) : left(l), right(r), max(m), sum(s) {}
	Node() : left(INF), right(INF), max(INF), sum(0) {}
};

Node trashValue(INF, INF, INF, 0);

vector<int> in;
vector<Node> segmentTree;
/**
* node : index (1 ~ 
* [start, end] : 현재 구간
* left, right : query로 구해야 하는 구간
*/
Node Query(int node, int start, int end, int left, int right) {
	if (start > right || end < left) return trashValue;

	if (start >= left && end <= right) { // 완전히 포함
		return segmentTree[node];
	}

	int mid = start + (end - start) / 2;
	Node leftChild = Query(node * 2, start, mid, left, right);
	Node rightChild = Query(node * 2 + 1, mid + 1, end, left, right);

	// 쉬운 이해를 위해 나눠서..
	int nowLeft = max(leftChild.left, leftChild.sum + rightChild.left);
	int nowRight = max(rightChild.right, leftChild.right + rightChild.sum);
	int nowSum = leftChild.sum + rightChild.sum;
	int nowMax = max({ leftChild.max, rightChild.max, leftChild.right + rightChild.left });

	Node ret(nowLeft, nowRight, nowMax, nowSum);
	return ret;
}

/**
* node : index (1 ~ 
* [start, end]
*/
Node MakeTree(int node, int start, int end) {
	if (start == end) {
		return segmentTree[node] = { in[start],in[start] ,in[start] ,in[start] };
	}

	int mid = start + (end - start) / 2;
	Node leftChild = MakeTree(node * 2, start, mid);
	Node rightChild = MakeTree(node * 2 + 1, mid + 1, end);

	// 쉬운 이해를 위해 나눠서..
	int nowLeft = max(leftChild.left, leftChild.sum + rightChild.left);
	int nowRight = max(rightChild.right, leftChild.right + rightChild.sum);
	int nowSum = leftChild.sum + rightChild.sum;
	int nowMax = max({ leftChild.max, rightChild.max, leftChild.right + rightChild.left });
	segmentTree[node] = { nowLeft, nowRight, nowMax, nowSum };

	return segmentTree[node];
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	int N{}; cin >> N;
	in.assign(N, 0);
	for (int& v : in) cin >> v;

	int tmpN{ 1 };
	while (tmpN < N) tmpN <<= 1;
	tmpN <<= 1;
	segmentTree.assign(tmpN, Node());

	MakeTree(1, 0, N - 1);

	int M; cin >> M;
	for (int m{}; m < M; ++m) {
		int a, b; cin >> a >> b; --a, --b;
		cout << Query(1, 0, N - 1, a, b).max << '\n';
	}

	return 0;
}