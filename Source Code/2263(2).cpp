// 8932KB, 32ms
#include<iostream>
#include<vector>
#include<algorithm>

using std::cin;
using std::cout;
using std::vector;

void print_inorder(const vector<int> &inOrderDAT, const vector<int> &postorder, const vector<int> &inorder, int post_start, int post_end, int in_start, int in_end)
{
	if (post_start >= post_end || in_start >= in_end) return;
	int root = postorder.at(post_end - 1);
	int root_index = inOrderDAT[root];
	cout << root << " ";
	print_inorder(inOrderDAT, postorder, inorder, post_start, post_start + root_index - in_start, in_start, root_index);
	print_inorder(inOrderDAT, postorder, inorder, post_start + root_index - in_start, post_end - 1, root_index + 1, in_end);
}

int main() {
	cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	int n;
	cin >> n;
	vector<int> inorder(n, 0), postorder(n,0), inOrderDAT(n + 1,0);
	for (int i = 0; i < n; ++i) {
		cin >> inorder[i];
		inOrderDAT[inorder[i]] = i;
	}
	for (int i = 0; i < n; ++i) {
		cin >> postorder[i];
	}
	print_inorder(inOrderDAT, postorder, inorder, 0, n, 0, n);
	return 0;
}