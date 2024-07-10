// https://m.blog.naver.com/kks227/221400656663
// Merge Sort Tree ����

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int tmpN = 1;

// ���� [s, e) ���̿��� k���� ū ���� ������ ���� : BottomUp
int Query(vector<vector<int>>& mergeSortTree, int s, int e, int k) {
	int answer{ };
	s = s + tmpN - 1, e = e + tmpN - 1;
	while (s <= e) { // ��ȣ ����
		if ((s & 1) == 1) answer += static_cast<int>(distance(upper_bound(begin(mergeSortTree[s]), end(mergeSortTree[s]), k), end(mergeSortTree[s]))); // right child(e^0�� right child�� �ǹ����� ����)
		if ((e & 1) == 0) answer += static_cast<int>(distance(upper_bound(begin(mergeSortTree[e]), end(mergeSortTree[e]), k), end(mergeSortTree[e]))); // left child(e^1�� left child�� �ǹ����� ����)

		s = (s + 1) >> 1;
		e = (e - 1) >> 1;
	}
	return answer;
}

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);

	int N{}; cin >> N;

	while (tmpN < N) tmpN <<= 1;
	tmpN <<= 1;

	vector<vector<int>> mergeSortTree(tmpN, vector<int>());
	tmpN >>= 1; // leaf node�� ����

	// leaf node �����
	for (int n{}; n < N; ++n) {
		int a{}; cin >> a;
		mergeSortTree[tmpN + n].push_back(a);
	}

	// Construct (bottom up)
	for (int v = tmpN - 1; v > 0; --v) {
		int left{ v << 1 }, right{ (v << 1) + 1 }; // warning ����
		vector<int>& now = mergeSortTree[v],
			& l = mergeSortTree[left], & r = mergeSortTree[right];
		now.resize(l.size() + r.size(), 0); // size ����
		for (int i{}, lIdx{}, rIdx{}; i < now.size(); ++i) { // ������������ �ֱ�
			if (rIdx == r.size() || (lIdx < l.size() && l[lIdx] < r[rIdx])) now[i] = l[lIdx++];
			else now[i] = r[rIdx++];
		}
	}

	int M{}; cin >> M; // Query ����
	int lastAns{};
	for (int m{}; m < M; ++m) {
		int a{}, b{}, c{};
		cin >> a >> b >> c;
		lastAns = Query(mergeSortTree, a ^ lastAns, b ^ lastAns, c ^ lastAns);
		cout << lastAns << '\n';
	}
	return 0;
}