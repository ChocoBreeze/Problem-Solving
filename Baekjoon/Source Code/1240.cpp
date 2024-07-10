// 중위 순회 - 트리 복구
#include <iostream>
#include <vector>
#include <utility>

using namespace std;
using pii = pair<int, int>;
constinit const int NOTREACH = -1;

vector<vector<pii>> graph; // to, weight

int DFS(int curr, int goal, int prev = -1) {
	if (curr == goal) {
		return 0;
	}
	for (pii& e : graph[curr]) {
		if (e.first == prev) continue;
		int ret = DFS(e.first, goal, curr);
		if (ret!=NOTREACH) return e.second + DFS(e.first, goal, curr);
	}
	return -1; // 도달하지 못 한 경우
}

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int N{}, M{};
	cin >> N >> M;
	graph = vector<vector<pii>>(N + 1);
	for (int n = 1; n < N; ++n) {
		int a{}, b{}, w{}; cin >> a >> b >> w;
		graph[a].emplace_back(b, w);
		graph[b].emplace_back(a, w);
	}

	while (M--) {
		int a{}, b{}; cin >> a >> b;
		cout << DFS(a, b) << '\n';
	}

	return 0;
}