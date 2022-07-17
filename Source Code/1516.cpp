#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	int N;
	cin >> N;
	vector<int> cost (N+1,0); // 1 ~ N
	vector<int> indegree(N+1,0); // 1 ~ N
	vector<vector<int>> edges(N + 1); // 1 ~ N
	for (int i = 1; i <= N;++i) {
		cin >> cost[i];
		while (1) {
			int tmp;
			cin >> tmp;
			if (tmp == -1) break;
			edges[tmp].push_back(i);
			++indegree[i];
		}
	}
	vector<int> answer(N + 1, 0);
	priority_queue<int, vector<int>, greater<int>> PQ;
	for (int i = 1; i <= N; ++i) {
		if (!indegree[i]) PQ.push(i);
	}
	vector<bool> chk(N + 1, false);
	while (!PQ.empty()) {
		int now = PQ.top();
		PQ.pop();
		if (chk[now]) continue;
		chk[now] = true;
		answer[now] += cost[now];
		for (auto& i : edges[now]) {
			answer[i] = max(answer[i], answer[now]);
			if (!(--indegree[i])) PQ.push(i);
		}
	}
	for (auto i = begin(answer) + 1; i != end(answer); ++i) {
		cout << *i << "\n";
	}

	return 0;
}