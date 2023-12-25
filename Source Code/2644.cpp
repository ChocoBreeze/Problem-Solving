#include <iostream>
#include <vector>

using namespace std;
vector<vector<int>> graph;

int DFS(int curr, int prev, int target) {
	if (curr == target) return 0;

	for (int& next : graph[curr]) {
		if (next == prev) continue;
		int dist = DFS(next, curr, target);
		if (dist != -1) return 1 + dist; // ÃÌ¼ö Á¸Àç
	}
	return -1; // ÃÌ¼ö °è»ê ¸ø ÇÔ.
}

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int n{}; cin >> n;
	graph = vector<vector<int>>(n); // 0 ~ n - 1
	int a{}, b{}; cin >> a >> b; --a, --b;

	int m{}; cin >> m;
	for (int i{}; i < m; ++i) {
		int x{}, y{}; cin >> x >> y; --x, --y;
		graph[x].push_back(y);
		graph[y].push_back(x);
	}

	cout << DFS(a, -1, b) << '\n';

	return 0;
}