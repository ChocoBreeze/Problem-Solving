// https://m.blog.naver.com/kks227/221400656663
// Merge Sort Tree 공부

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int tmpN = 1;

// 구간 [s, e) 사이에서 k보다 큰 값의 개수를 리턴 : BottomUp
int Query(vector<vector<int>>& mergeSortTree, int s, int e, int k) {
	int answer{ };
	s = s + tmpN - 1, e = e + tmpN - 1;
	while (s <= e) { // 등호 포함
		if ((s & 1) == 1) answer += static_cast<int>(distance(upper_bound(begin(mergeSortTree[s]), end(mergeSortTree[s]), k), end(mergeSortTree[s]))); // right child(e^0이 right child를 의미하지 않음)
		if ((e & 1) == 0) answer += static_cast<int>(distance(upper_bound(begin(mergeSortTree[e]), end(mergeSortTree[e]), k), end(mergeSortTree[e]))); // left child(e^1이 left child를 의미하지 않음)

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
		lastAns = Query(mergeSortTree, a ^ lastAns, b ^ lastAns, c ^ lastAns);
		cout << lastAns << '\n';
	}
	return 0;
}