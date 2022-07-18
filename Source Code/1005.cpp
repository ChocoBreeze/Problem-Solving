#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	int T, N, K, W;
	cin >> T;
	for (int t = 0; t < T; ++t) {
		cin >> N >> K;
		vector<int> cost(N + 1, 0);
		vector<int> indegrees(N + 1, 0);
		for (int c = 1; c <= N;++c) {
			cin >> cost[c];
		}
		vector<vector<int>> edges(N + 1); // 1 ~ N
		int a, b;
		for (int k = 0; k < K; ++k) {
			cin >> a >> b;
			edges[a].push_back(b);
			indegrees[b]++;
		}
		cin >> W;
		priority_queue<int, vector<int>, greater<int>> PQ;
		for (int i = 1; i <= N;++i) {
			if (indegrees[i] == 0) PQ.push(i);
		}
		vector<int> answer_cost(N+1,0);
		while (!PQ.empty()) {
			int now = PQ.top();
			answer_cost[now] += cost[now];
			if (now == W) break;
			PQ.pop();
			for (auto& i : edges[now]) {
				if (!(--indegrees[i])) PQ.push(i);
				answer_cost[i] = max(answer_cost[i], answer_cost[now]);
			}
		}
		cout << answer_cost[W] << "\n";
	}
	
	return 0;
}