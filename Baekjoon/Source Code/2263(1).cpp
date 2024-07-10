// inorder(중위) : left - root - right
// postorder(후위) : left - right - root
// preorder(전위) : root - left -right
// 266가지 문제로 정복하는 코딩 인터뷰 in C++

#include<iostream>
#include<memory> // unique_ptr
#include<vector>
#include<unordered_map>

using std::cin;
using std::cout;
using std::unique_ptr;
using std::unordered_map;
using std::vector;
using std::make_unique;

template <typename T>
struct BinaryTreeNode {
	T data;
	unique_ptr<BinaryTreeNode<T>> left; 
	unique_ptr<BinaryTreeNode<T>> right;
	BinaryTreeNode(T data_, unique_ptr<BinaryTreeNode<T>> left_, unique_ptr<BinaryTreeNode<T>> right_) 
		: data(data_), left(std::move(left_)), right(std::move(right_)) {}
};

unique_ptr<BinaryTreeNode<int>> BinaryTreeFromPostorderInorderHelper(const vector<int>& postorder, int postorder_start, int postorder_end,
	int inorder_start, int inorder_end, const unordered_map<int, int>& node_to_inorder_idx) {
	if (postorder_end <= postorder_start || inorder_end <= inorder_start) {
		return nullptr;
	}
	size_t root_inorder_idx = node_to_inorder_idx.at(postorder[postorder_end - 1]);
	size_t left_subtree_size = root_inorder_idx - inorder_start;

	return make_unique<BinaryTreeNode<int>>(
		// root
		postorder[postorder_end - 1],
		// 재귀적으로 왼쪽 부분 트리를 구함 (마지막 노드 제외)
		BinaryTreeFromPostorderInorderHelper(postorder, postorder_start , postorder_start + left_subtree_size, inorder_start, root_inorder_idx, node_to_inorder_idx),
		// 재귀적으로 오른쪽 부분 트리를 구함.
		BinaryTreeFromPostorderInorderHelper(postorder, postorder_start + left_subtree_size, postorder_end - 1, root_inorder_idx + 1, inorder_end, node_to_inorder_idx));
}

unique_ptr<BinaryTreeNode<int>> BinaryTreeFromPostorderInorder(const vector<int>& postorder, const vector<int>& inorder) {
	unordered_map<int, int> node_to_inorder_idx;
	for (int i = 0; i < size(inorder); ++i) {
		node_to_inorder_idx.emplace(inorder[i], i);
	}
	return BinaryTreeFromPostorderInorderHelper(postorder, /*postorder_start=*/0, size(postorder), /*inorder_start=*/0, size(inorder), node_to_inorder_idx);
}

void TreeTraversal(const unique_ptr<BinaryTreeNode<int>>& root) {
	if (root) {
		cout << root->data << " ";
		TreeTraversal(root->left);
		TreeTraversal(root->right);
	}
}

int main() {
	cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	int n;
	cin >> n;
	vector<int> inorder(n, 0), postorder(n,0);
	for (int i = 0; i < n; ++i) {
		cin >> inorder[i];
	}
	for (int i = 0; i < n; ++i) {
		cin >> postorder[i];
	}
	auto Tree = BinaryTreeFromPostorderInorder(postorder, inorder);
	TreeTraversal(Tree);
	return 0;
}