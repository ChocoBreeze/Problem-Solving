#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using pii = pair<int, int>;
constinit const int MAXN = 10'001;

struct Info {
	int now, left, right;
	Info(int now, int left, int right) : now(now), left(left), right(right) {}
	Info() : Info(0, 0, 0) {}
};
vector<Info> infos;

vector<pii> levelInterval; // levelInterval[i] : i��° level�� {������, �����}
int x, maxLevel; 
void DFS(int curr, int level) {
	maxLevel = max(maxLevel, level);
	auto& [now, left, right] = infos[curr];
	if (left != -1) {
		DFS(left, level + 1);
	}
	
	auto& [first, second] = levelInterval[level];
	first = min(first, x);
	second = max(second, x);
	++x; // ���� ��ǥ

	if (right != -1) {
		DFS(right, level + 1);
	}
}

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int N{}; cin >> N;
	// Ʈ���� ������ ���� ���ʿ� �ִ� ��Ʈ ��尡 1�̰� �Ʒ��� 1�� �����Ѵ�.
	infos = vector<Info>(N + 1);
	vector<bool> isRoot(N + 1, true);
	for (int n{}; n < N; ++n) {
		int v, l, r; cin >> v >> l >> r;
		infos[v] = Info(v, l, r);
		if (l != -1) isRoot[l] = false;
		if (r != -1) isRoot[r] = false;
	}

	// root ã��
	// 1 ~ N ������ ��� ������ ���� ��Ʈ�� �����ϰ� �����ϸ�
	// ���� ����� ������ �ʴ� ��찡 �ִ�.(���� ����Ʈ���� �ִ� ���)
	int root{};
	for (int n = 1; n <= N; ++n) {
		if (isRoot[n]) {
			root = n;
			break;
		}
	}
	
	pii answer(1, -1); // {level, maxInterval}
	x = 1;
	maxLevel = -1;
	levelInterval.assign(MAXN, make_pair(MAXN, -1));

	DFS(root, 1); // ��Ʈ ��� = root, ���� = 1
	for (int level = 1; level <= maxLevel; ++level) {
		auto& [first, second] = levelInterval[level];
		if (second - first + 1 > answer.second) { // ������ �� ���� ������ ����
			answer = { level, second - first + 1 };
		}
		else if (second - first + 1 == answer.second) {
		}
	}

	cout << answer.first << ' ' << answer.second << '\n';
	return 0;
}