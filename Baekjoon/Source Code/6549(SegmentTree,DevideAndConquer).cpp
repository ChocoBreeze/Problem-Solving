// segment tree + divide & conquer

#include <iostream>
#include <climits>
#include <algorithm>
#include <vector>

using namespace std;
const int MAXH = 2000000000;
using ll = long long;
int tmpN{ 1 };

vector<int> heights;
vector<int> segTree;

void makeTree(int idx) {
	while (idx > 1) {
		int parent = idx >> 1;
		if (heights[segTree[parent * 2]] <= heights[segTree[parent * 2 + 1]]) {
			segTree[parent] = segTree[parent * 2];
		}
		else {
			segTree[parent] = segTree[parent * 2 + 1];
		}
		idx = parent;
	}
}

int query(int left, int right) { // 최소 높이를 가지는 index 리턴
	left = left + tmpN;
	right = right + tmpN;
	int minH = INT_MAX;
	int ret{};
	// 항상 헷갈린다
	while(left <= right) {
		if ((left & 1) == 1) { // 여기랑
			if (minH > heights[segTree[left]]) {
				minH = heights[segTree[left]];
				ret = segTree[left];
			}
		}
		if ((right & 1) == 0) { // 여기랑
			if (minH > heights[segTree[right]]) {
				minH = heights[segTree[right]];
				ret = segTree[right];
			}
		}
		left = (left + 1) >> 1; // 여기랑
		right = (right - 1) >> 1; // 여기랑
	}

	return ret;
}

ll solve(int left, int right) {
	if (left > right) return 0ll;
	if (left == right) {
		return static_cast<ll>(heights[left]);
	}
	ll answer = -1;

	int minIndex = query(left, right);
	ll minH = static_cast<ll>(heights[minIndex]);
	answer = max(answer, minH * (right - left + 1));

	answer = max(answer, solve(left, minIndex - 1));
	answer = max(answer, solve(minIndex + 1, right));

	return answer;
}

int main() {
	int n;
	cin.tie(NULL)->sync_with_stdio(false);
	while (1) {
		cin >> n;
		if (n == 0) break; // EOF

		while (tmpN < n) tmpN <<= 1;
		heights = vector<int>(tmpN << 1, MAXH);
		segTree = vector<int>(tmpN << 1, 0);
		for (int i = 0; i < n; ++i) {
			cin >> heights[i];
		}
		for (int i = 0; i < tmpN; ++i) {
			segTree[tmpN + i] = i;
			makeTree(tmpN + i);
		}
		cout << solve(0, n - 1) << '\n';
	}
	return 0;
}