#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> graph;
int answer{}, delNode{};

void Dfs(int curr) {
	int cnt{};
	for (int& next : graph[curr]) {
		if (next == delNode) continue;
		cnt++;
		Dfs(next);
	}
	if (cnt == 0) ++answer;
}

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int N{}; cin >> N; // 노드 개수
	graph = vector<vector<int>>(N);

	int rootNode{};
	for (int n{}; n < N; ++n) {
		int in{}; cin >> in;
		if (in == -1) rootNode = n;
		else {
			graph[in].push_back(n);
		}
	}
	cin >> delNode;

	if (delNode != rootNode) {
		Dfs(rootNode);
	}
	cout << answer << '\n';

	return 0;
}