// 참고) 금광 세그.. 
// https://viyoung.tistory.com/149
// https://blog.naver.com/jinhan814/222172647341
// https://seungwuk98.tistory.com/39
// https://blog.naver.com/melon940925/222135733526
// 분할 정복 + segment Tree

// 6120KB, 52ms
// bottomUp
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

vector<Node> segmentTree;

int Query(int s, int e, int tmpN) {
	s = s + tmpN - 1, e = e + tmpN - 1;
	Node sNode, eNode; // leftChild, rightChild
	while (s <= e) {
		if ((s & 1) == 1) { // sNode = leftChild
			Node rightChild = segmentTree[s];
			int nextLeft = max(sNode.left, sNode.sum + rightChild.left);
			int nextRight = max(rightChild.right, sNode.right + rightChild.sum);
			int nextSum = sNode.sum + rightChild.sum;
			int nextMax = max({ sNode.max, rightChild.max, sNode.right + rightChild.left });
			sNode = { nextLeft, nextRight, nextMax, nextSum };
		}
		if ((e & 1) == 0) { // eNode = rightChild
			Node leftChild = segmentTree[e];
			int nextLeft = max(leftChild.left, leftChild.sum + eNode.left);
			int nextRight = max(eNode.right, leftChild.right + eNode.sum);
			int nextSum = leftChild.sum + eNode.sum;
			int nextMax = max({ leftChild.max, eNode.max, leftChild.right + eNode.left});
			eNode = { nextLeft, nextRight, nextMax, nextSum };
		}
		s = (s + 1) >> 1;
		e = (e - 1) >> 1;
	}
	return max({sNode.max, eNode.max, sNode.right + eNode.left});
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	int N{}; cin >> N;

	int tmpN{ 1 };
	while (tmpN < N) tmpN <<= 1;
	tmpN <<= 1;
	segmentTree.assign(tmpN, Node(INF, INF, INF, 0));
	tmpN >>= 1;
	
	for (int i{}; i < N; ++i) {
		int in; cin >> in;
		segmentTree[i + tmpN] = Node(in, in, in, in);
	}

	for (int i{ tmpN - 1 }; i >= 1; --i) { // makeTree
		Node& left = segmentTree[i << 1];
		Node& right = segmentTree[(i << 1) + 1];
		segmentTree[i].left = max(left.left, left.sum + right.left);
		segmentTree[i].right = max(left.right + right.sum, right.right);
		segmentTree[i].max = max({ left.max, right.max, left.right + right.left });
		segmentTree[i].sum = left.sum + right.sum;
	}

	int M; cin >> M;
	for (int m{}; m < M; ++m) {
		int a, b; cin >> a >> b;
		cout << Query(a, b, tmpN) << '\n';
	}

	return 0;
}