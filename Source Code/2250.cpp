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

vector<pii> levelInterval; // levelInterval[i] : i번째 level의 {시작점, 출발점}
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
	++x; // 다음 좌표

	if (right != -1) {
		DFS(right, level + 1);
	}
}

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int N{}; cin >> N;
	// 트리의 레벨은 가장 위쪽에 있는 루트 노드가 1이고 아래로 1씩 증가한다.
	infos = vector<Info>(N + 1);
	vector<bool> isRoot(N + 1, true);
	for (int n{}; n < N; ++n) {
		int v, l, r; cin >> v >> l >> r;
		infos[v] = Info(v, l, r);
		if (l != -1) isRoot[l] = false;
		if (r != -1) isRoot[r] = false;
	}

	// root 찾기
	// 1 ~ N 번까지 모든 정점에 대해 루트로 간주하고 시작하면
	// 답이 제대로 나오지 않는 경우가 있다.(왼쪽 서브트리만 있는 경우)
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

	DFS(root, 1); // 루트 노드 = root, 레벨 = 1
	for (int level = 1; level <= maxLevel; ++level) {
		auto& [first, second] = levelInterval[level];
		if (second - first + 1 > answer.second) { // 같으면 더 작은 레벨이 정답
			answer = { level, second - first + 1 };
		}
		else if (second - first + 1 == answer.second) {
		}
	}

	cout << answer.first << ' ' << answer.second << '\n';
	return 0;
}