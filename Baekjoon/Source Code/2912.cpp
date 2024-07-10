// https://m.blog.naver.com/kks227/221400656663 : ���̵��
// Merge Sort Tree
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int tmpN{ 1 }, answer = 0;
vector<int> candidate, candiVisited, cnt;

void AddCandidate(vector<vector<int>>& mergeSortTree, int index) {
	int len = static_cast<int>(mergeSortTree[index].size());
	if (len == 1) {
		if (candiVisited[mergeSortTree[index].front()] == 0) {
			candidate.push_back(mergeSortTree[index].front());
			candiVisited[mergeSortTree[index].front()] = 1;
		}
	}
	else { // 1���� �ƴ� ��쿡 len�� ������ ¦��..
		int half = len >> 1;
		if (mergeSortTree[index][half - 1] == mergeSortTree[index][half]) {
			if (candiVisited[mergeSortTree[index][half]] == 0) {
				candidate.push_back(mergeSortTree[index][half]);
				candiVisited[mergeSortTree[index][half]] = 1;
			}
		}
	}
}

void GetCandidate(vector<vector<int>>& mergeSortTree, int s, int e, int node = 1, int ns = 0, int ne = tmpN) {
	if (ne <= s || e <= ns) return; // ���� ��
	if (s <= ns && ne <= e) { // ������ ���� ��
		AddCandidate(mergeSortTree, node);
		return;
	}
	// �ڽ��� ���� ���� �̵�
	int mid = ns + (ne - ns) / 2;
	GetCandidate(mergeSortTree, s, e, node * 2, ns, mid);
	GetCandidate(mergeSortTree, s, e, node * 2 + 1, mid, ne);
}

void Count(vector<int>& now, int candi) {
	auto ret = equal_range(begin(now), end(now), candi);
	cnt[candi] += static_cast<int>(distance(ret.first, ret.second));
}

// [ns, ne)
void Query(vector<vector<int>>& mergeSortTree, int s, int e, int node = 1, int ns = 0, int ne = tmpN) {
	if (ne <= s || e <= ns) return; // ���� ��
	if (s <= ns && ne <= e) { // ������ ���� ��
		for (int& candi : candidate) {
			Count(mergeSortTree[node], candi);
			if (cnt[candi] > (e - s) / 2) answer = candi;
		}
		return;
	}
	// �ڽ��� ���� ���� �̵�
	int mid = ns + (ne - ns) / 2;
	if (answer) return; // �� �� �ʿ� ����.
	Query(mergeSortTree, s, e, node * 2, ns, mid);
	if (answer) return; // �� �� �ʿ� ����.
	Query(mergeSortTree, s, e, node * 2 + 1, mid, ne);
}


int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int N{}, C{};
	cin >> N >> C;

	while (tmpN < N) tmpN <<= 1;

	tmpN <<= 1;
	vector<vector<int>> mergeSortTree(tmpN);
	vector<int> leaf(N, 0);
	tmpN >>= 1;

	for (int n{}; n < N; ++n) {
		cin >> leaf[n];
		mergeSortTree[tmpN + n].push_back(leaf[n]);
	}

	for (int n = tmpN - 1; n > 0; --n) {
		int left = n << 1, right = left + 1;
		vector<int>& now = mergeSortTree[n], & l = mergeSortTree[left], & r = mergeSortTree[right];
		now.resize(l.size() + r.size(), 0);
		for (int i{}, lIdx{}, rIdx{}; i < static_cast<int>(now.size()); ++i) {
			if (rIdx == static_cast<int>(r.size()) || (lIdx < static_cast<int>(l.size()) && l[lIdx] < r[rIdx])) now[i] = l[lIdx++];
			else now[i] = r[rIdx++];
		}
	}

	// �� �������� �ĺ��� ���ϴ� ���̵��..
	// ���� ���� 2k���� Ư�� ���� ���ݼ��� �Ƿ��� k-1��°, k��° ���� ���ƾ� ��.
	// �ش� �������� �ĺ��� �� �� �ִٸ�, �ش� ������ ������ ���� ���������� �ĺ��� �Ǿ�� ��.

	int M{};
	cin >> M; // ���� �� = ���� ��
	for (int m{}; m < M; ++m) {
		int a{}, b{}; // 1<= a <= b <= N
		cin >> a >> b;

		// candidate
		vector<int>().swap(candidate);
		candiVisited.assign(C + 1, 0);
		GetCandidate(mergeSortTree, a - 1, b);

		// �� ���ϱ�
		answer = 0;
		cnt.assign(C + 1, 0);
		Query(mergeSortTree, a - 1, b);
		if (answer == 0) cout << "no\n";
		else cout << "yes " << answer << '\n';
	}

	return 0;
}