// https://www.acmicpc.net/board/view/80148
// 갈 수 없는 애들만 카운팅해서 답 나옴
// kosaraju
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

vector<vector<int>> graph, revGraph;
vector<int> visited;
stack<int> S;

void FillStack(int curr) {
	visited[curr] = 1;

	for (int& next : graph[curr]) {
		if (!visited[next]) {
			FillStack(next);
		}
	}

	S.push(curr);
}

void FindSCC(int curr) { // revGraph 대신 graph
	visited[curr] = 1; 

	for (int& next : graph[curr]) {
		if (!visited[next]) {
			FindSCC(next);
		}
	}
}


int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	int T{}; cin >> T;

	for (int t{}; t < T; ++t) {
		int N, M; cin >> N >> M; // 정점 수, 간선 수
		graph = vector<vector<int>>(N + 1);
		revGraph = vector<vector<int>>(N + 1);
		for (int m{}; m < M; ++m) {
			int a, b; cin >> a >> b;
			graph[a].push_back(b);
			revGraph[b].push_back(a);
		}

		visited = vector<int>(N + 1, 0);
		for (int n{ 1 }; n <= N; ++n) {
			if (!visited[n]) {
				FillStack(n);
			}
		}
		
		fill(begin(visited), end(visited), 0);
		
		int ans{};
		while (!S.empty()) {
			int now = S.top(); S.pop();
			if (!visited[now]) {
				FindSCC(now);
				++ans;
			}
		}
		cout << ans << '\n';
	}

	return 0;
}