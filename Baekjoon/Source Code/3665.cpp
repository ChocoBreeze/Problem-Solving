/*
T(100)* { n ^ 2(250000) + m }
만약, 확실한 순위를 찾을 수 없다면 "?"를 출력 => q에 size가 2개 이상 => 실제로 나올 수 없는 경우임(이 문제에서는).
? 출력 관련해서 찾아보려다가 결국은 없다는 것을 알아차리는 것이 포인트인 듯함! => 시간이 오래 걸림.
데이터에 일관성이 없어서 순위를 정할 수 없는 경우에는 "IMPOSSIBLE"을 출력 = > 사이클이 생기는 경우(모든 정점을 다 방문하지 않았는데 큐가 빈 경우)

바로 이전 등수인 애꺼만 간선추가하는 것이 아닌
앞에 있는 애들거는 모두 다 추가 + 바뀐 간선은 바꿔서 추가 -> DAG 판단.
*/

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);

	int T; cin >> T;
	while (T--) {
		int n; cin >> n; // 팀의 수
		vector<int> teams(n, 0);
		for (int& t : teams) cin >> t;

		vector<vector<int>> graph(n + 1); // 1 ~ n
		vector<vector<int>> adj(n + 1, vector<int>(n + 1, 0)); // 1 ~ n
		vector<int> indegrees(n + 1, 0); // 1 ~ n

		int m; cin >> m; // 상대적인 등수가 바뀐 쌍의 수
		for (int i{}; i < m; ++i) {
			int a, b; cin >> a >> b;
			adj[a][b] = 1;
			adj[b][a] = 1;
		}

		// Edge 구성
		for (int i{}; i < n; ++i) {
			for (int j{ i + 1 }; j < n; ++j) {
				int first{ teams[i] }, second{ teams[j] }; // i -> j

				if (adj[first][second]) { // 반대로 넣어야 함
					swap(first, second);
				}

				graph[first].push_back(second);
				indegrees[second]++;
			}
		}
		queue<int> q;
		for (int i{ 1 }; i <= n; ++i) {
			if (indegrees[i] == 0) q.push(i);
		}

		vector<int> answer;
		answer.reserve(n);
		int chk = 0;
		while (!q.empty()) {
			int now = q.front(); q.pop();
			answer.push_back(now);

			for (int& next : graph[now]) {
				indegrees[next]--;
				if (indegrees[next] == 0) q.push(next);
				if (q.size() >= 2) chk = 2;
			}
			if (chk == 2) break;
		}

		if (answer.size() != n) chk = 1;

		if (chk == 2) cout << "?\n"; // 고려는 했지만 사실 이런 답이 나올 수 있는 경우의 수는 없음.
		else if (chk == 1) cout << "IMPOSSIBLE\n";
		else {
			for (int& a : answer) cout << a << ' ';
			cout << '\n';
		}
	}
	
	return 0;
}