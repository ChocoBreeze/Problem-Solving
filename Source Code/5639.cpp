// preorder : root - left - right
// postorder : left - right -root 5 28 24 45 30 60 52 98 50
#include<iostream>
#include<vector>

using std::vector;
using std::cin;
using std::cout;

void print_postorder(vector<int>& preorder, int start, int end) {
	if (start == end) return; // empty
	if (start + 1 == end) {
		cout << preorder[start] << "\n";
		return;
	}
	int root = preorder[start];
	int left_tree_size = end - start - 1;
	for (int i = start + 1; i < end; ++i) {
		if (preorder[i] > root) {
			left_tree_size = i - start - 1;
			break;
		}
	}
	print_postorder(preorder, start + 1, start + 1 + left_tree_size);
	print_postorder(preorder, start + 1 + left_tree_size, end);
	cout << root << "\n";
}

int main() {
	cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	vector<int> preorder_path;
	int temp;
	while (cin >> temp) {
		preorder_path.push_back(temp);
	}
	print_postorder(preorder_path,0,size(preorder_path));
	return 0;
}