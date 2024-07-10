#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
vector<vector<int>> graph, DP;
vector<int> weights, visited;

void Dfs(int curr) {
	DP[curr][0] = 0;
	DP[curr][1] = weights[curr];
	for (int& next : graph[curr]) {
		if (visited[next]) continue;
		visited[next] = 1;
		Dfs(next);
		visited[next] = 0;
		DP[curr][0] += max(DP[next][0], DP[next][1]);
		DP[curr][1] += DP[next][0];
	}
}

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int N{}; cin >> N; // 트리 정점 수

	graph = vector<vector<int>>(N + 1);
	DP = vector<vector<int>>(N + 1, vector<int>(2, -1));

	const int SIZE = N + 1;
	weights.assign(SIZE, 0);
	visited.assign(SIZE, 0);

	for (int i{ 1 }; i <= N; ++i) {
		cin >> weights[i];
	}
	for (int n{}; n < N - 1; ++n) {
		int a{}, b{}; cin >> a >> b;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}

	visited[1] = 1;
	Dfs(1);
	visited[1] = 0;

	cout << max(DP[1][0], DP[1][1]) << '\n';
	return 0;
}