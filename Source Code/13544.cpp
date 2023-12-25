// https://m.blog.naver.com/kks227/221400656663
// Merge Sort Tree 공부

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int tmpN = 1;

// 구간 [s, e) 사이에서 k보다 큰 값의 개수를 리턴 : TopDown
int Query(vector<vector<int>>& mergeSortTree, int s, int e, int k, int node = 1, int ns = 0, int ne = tmpN) {
	// 자신이 완전히 구간 밖
	if (ne <= s || e <= ns) return 0;
	// 자신이 완전히 구간 안: 이 노드의 결과를 돌려줌
	if (s <= ns && ne <= e) {
		return static_cast<int>(distance(upper_bound(mergeSortTree[node].begin(), mergeSortTree[node].end(), k), mergeSortTree[node].end()));
	}

	// 자신의 양쪽 노드의 답을 구해 더해서 돌려줌
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
	tmpN >>= 1; // leaf node의 시작

	// leaf node 만들기
	for (int n{}; n < N; ++n) {
		int a{}; cin >> a;
		mergeSortTree[tmpN + n].push_back(a);
	}

	// Construct (bottom up)
	for (int v = tmpN - 1; v > 0; --v) {
		int left{ v << 1 }, right{ (v << 1) + 1 }; // warning 제거
		vector<int>& now = mergeSortTree[v],
			& l = mergeSortTree[left], & r = mergeSortTree[right];
		now.resize(l.size() + r.size(), 0); // size 조정
		for (int i{}, lIdx{}, rIdx{}; i < now.size(); ++i) { // 오름차순으로 넣기
			if (rIdx == r.size() || (lIdx < l.size() && l[lIdx] < r[rIdx])) now[i] = l[lIdx++];
			else now[i] = r[rIdx++];
		}
	}

	int M{}; cin >> M; // Query 개수
	int lastAns{};
	for (int m{}; m < M; ++m) {
		int a{}, b{}, c{};
		cin >> a >> b >> c;
		lastAns = Query(mergeSortTree, (a ^ lastAns) - 1, b ^ lastAns, c ^ lastAns);
		cout << lastAns << '\n';
	}
	return 0;
}