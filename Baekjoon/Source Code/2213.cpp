#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <queue>

using namespace std;
using pii = pair<int, int>;
vector<vector<int>> graph, DP;
vector<vector<vector<pii>>> DPRestore; // (index, use)
vector<int> weights, visited;

void Dfs(int curr) {
	DP[curr][0] = 0;
	DP[curr][1] = weights[curr];
	for (int& next : graph[curr]) {
		if (visited[next]) continue;
		visited[next] = 1;
		Dfs(next);
		visited[next] = 0;

		int use = DP[next][0] > DP[next][1] ? 0 : 1;
		DP[curr][0] += DP[next][use];
		// DP[curr][0] += max(DP[next][0], DP[next][1]);
		DPRestore[curr][0].emplace_back(next, use);

		DP[curr][1] += DP[next][0]; // not use next
		DPRestore[curr][1].emplace_back(next, 0);
	}
}

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int N{}; cin >> N; // 트리 정점 수

	const int SIZE = N + 1;
	graph = vector<vector<int>>(SIZE);
	DP = vector<vector<int>>(SIZE, vector<int>(2, 0));
	DPRestore = vector<vector<vector<pii>>>(SIZE, vector<vector<pii>>(2));
	
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

	vector<int> answer;
	queue<pii> q;
	if (DP[1][0] > DP[1][1]) q.emplace(1, 0);
	else {
		q.emplace(1, 1); answer.push_back(1);
	}
	while (!q.empty()) {
		pii curr = q.front(); q.pop();
		for (pii& info : DPRestore[curr.first][curr.second]) {
			q.emplace(info);
			if (info.second) answer.push_back(info.first);
		}
	}
	sort(begin(answer), end(answer));
	for (int& a : answer) cout << a << ' ';
	cout << '\n';

	return 0;
}