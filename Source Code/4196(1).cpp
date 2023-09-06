// tarjan
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

vector<vector<int>> graph; // graph

vector<int> visited; // 방문 순서 저장
int dfsnIndex{};
vector<int> sn; // sn[i] : 정점 i가 속한 SCC 번호 (= kosaraju's SCCDAT)

vector<int> isFinish; // SCC가 결정된 경우 true
stack<int> S;

vector<vector<int>> SCC; // SCC[i] : i번째 SCC에 속한 V들.

int DFS(int curr) {
	visited[curr] = ++dfsnIndex;
	S.push(curr);

	// curr에서 갈 수 있는 정점 중 dfsn 최소 값을 result에 저장
	int result = visited[curr];
	for (int& next : graph[curr]) {
		if (visited[next] == 0) { // 미방문
			result = min(result, DFS(next));
		}
		else if(!isFinish[next]) {
			result = min(result, visited[next]);
		}
	}

	// 자신이 최소의 dfsn인 경우 -> SCC 추출
	if (result == visited[curr]) {
		vector<int> nowSCC;
		while (!S.empty()) {
			int t = S.top(); S.pop();
			nowSCC.push_back(t);
			sn[t] = static_cast<int>(SCC.size());
			isFinish[t] = 1;
			if (t == curr) break;
		}
		SCC.push_back(nowSCC);
	}
	return result;
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	int T{}; cin >> T;

	for (int t{}; t < T; ++t) {
		int N, M; cin >> N >> M; // 정점 수, 간선 수
		vector<vector<int>>().swap(SCC); // swap empty
		graph = vector<vector<int>>(N + 1);
		for (int m{}; m < M; ++m) {
			int a, b; cin >> a >> b;
			graph[a].push_back(b);
		}

		visited = vector<int>(N + 1, 0);
		isFinish = vector<int>(N + 1, 0);
		sn = vector<int>(N + 1, -1);
		for (int n{ 1 }; n <= N; ++n) {
			if (!visited[n]) {
				DFS(n);
			}
		}
		
		int ans = static_cast<int>(SCC.size());
		vector<int> indegrees(static_cast<int>(SCC.size()), 0);
		for (int i{}; i < static_cast<int>(SCC.size()); ++i) {
			for (int& node : SCC[i]) {
				for (int& next : graph[node]) {
					if (sn[next] == i) continue; // 같은 SCC
					indegrees[sn[next]]++;
					if (indegrees[sn[next]] == 1) --ans;
				}
			}
		}
		cout << ans << '\n';
	}

	return 0;
}