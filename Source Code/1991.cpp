#include<iostream>
#include<vector>
#include<string>

struct Node {
	int Left;
	int Right;
	Node(int l, int r) : Left(l), Right(r) {}
};

using std::cin;
using std::cout;
using std::vector;
using std::string;

string preorder(vector<Node>& tree, int index) { // root - left - right
	string str;
	str += (char)('A' + index); // root
	if (tree[index].Left != 0) str += preorder(tree, tree[index].Left);
	if (tree[index].Right != 0) str += preorder(tree, tree[index].Right);
	return str;
}

string inorder(vector<Node>& tree, int index) { // left - root - right
	string str;
	if (tree[index].Left != 0) str += inorder(tree, tree[index].Left);
	str += (char)('A' + index); // root
	if (tree[index].Right != 0) str += inorder(tree, tree[index].Right);
	return str;
}

string postorder(vector<Node>& tree, int index) { // left - right - root
	string str;
	if (tree[index].Left != 0) str += postorder(tree, tree[index].Left);
	if (tree[index].Right != 0) str += postorder(tree, tree[index].Right);
	str += (char)('A' + index); // root
	return str;
}


int main() {
	cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	int N; // 노드 개수
	cin >> N;
	// 항상 A 노드가 root이며, A부터 차례대로 입력이 주어짐.
	vector<Node> tree(N, Node(0, 0));
	char a, b, c;
	for (int i = 0; i < N; ++i) {
		cin >> a >> b >> c;
		int index = a - 'A';
		if (b != '.') tree[index].Left = b - 'A';
		if (c != '.') tree[index].Right = c - 'A';
	}
	cout << preorder(tree, 0) << "\n";
	cout << inorder(tree, 0) << "\n";
	cout << postorder(tree, 0) << "\n";
	return 0;
}