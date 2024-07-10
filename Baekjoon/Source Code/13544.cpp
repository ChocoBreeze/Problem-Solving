// https://m.blog.naver.com/kks227/221400656663
// Merge Sort Tree ����

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int tmpN = 1;

// ���� [s, e) ���̿��� k���� ū ���� ������ ���� : TopDown
int Query(vector<vector<int>>& mergeSortTree, int s, int e, int k, int node = 1, int ns = 0, int ne = tmpN) {
	// �ڽ��� ������ ���� ��
	if (ne <= s || e <= ns) return 0;
	// �ڽ��� ������ ���� ��: �� ����� ����� ������
	if (s <= ns && ne <= e) {
		return static_cast<int>(distance(upper_bound(mergeSortTree[node].begin(), mergeSortTree[node].end(), k), mergeSortTree[node].end()));
	}

	// �ڽ��� ���� ����� ���� ���� ���ؼ� ������
	int mid = ns + (ne - ns) / 2;
	return Query(mergeSortTree, s, e, k, node * 2, ns, mid) 
		+ Query(mergeSortTree, s, e, k, node * 2 + 1, mid, ne);
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
		lastAns = Query(mergeSortTree, (a ^ lastAns) - 1, b ^ lastAns, c ^ lastAns);
		cout << lastAns << '\n';
	}
	return 0;
}