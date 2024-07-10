#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;
vector<vector<int>> graph;

vector<int> visited; // 방문 순서 저장
int dfsnIndex{};

vector<int> isFinish; // SCC가 결정된 경우 true

vector<vector<int>> SCC; // SCC[i] : i번째 SCC에 속한 V들.
vector<int> SCCIndex; // SCCIndex[i] : i번째 정점이 속한 SCC 번호
vector<int> SCCDP; // SCCDP[i] : i번째 SCC에서 T에 도달가능한 경우 방문가능한 최대 정점 수
stack<int> s;

int DFS(int curr) {
	visited[curr] = ++dfsnIndex;
	s.push(curr);

	// curr에서 갈 수 있는 정점 중 dfsn 최소 값을 result에 저장
	int result = visited[curr];
	for (int& next : graph[curr]) {
		if (visited[next] == 0) { // 미방문
			result = min(result, DFS(next));
		}
		else if (!isFinish[next]) {
			result = min(result, visited[next]);
		}
	}

	// 자신이 최소의 dfsn인 경우 -> SCC 추출
	if (result == visited[curr]) {
		vector<int> nowSCC;
		while (!s.empty()) {
			int t = s.top(); s.pop();
			nowSCC.push_back(t);
			SCCIndex[t] = static_cast<int>(SCC.size());
			isFinish[t] = 1;
			if (t == curr) break;
		}
		sort(begin(nowSCC), end(nowSCC));
		SCC.push_back(nowSCC);
	}
	return result;
}

int SCCDFS(int curr, int goalSCCIdx) {
	int sccIdx = SCCIndex[curr]; // 현재 정점이 속한 scc 번호
	if (sccIdx == goalSCCIdx) { // 도달
		return SCCDP[sccIdx] = static_cast<int>(SCC[sccIdx].size());
	}

	int maxV{-1};
	for (int& sccV : SCC[sccIdx]) { // 정점마다
		for (int& next : graph[sccV]) { // sccV에서 갈 수 있는 next 정점
			if (SCCIndex[next] == sccIdx) continue; // 현재랑 같은 SCC

			if (SCCDP[SCCIndex[next]]) maxV = max(maxV, SCCDP[SCCIndex[next]]);
			else maxV = max(maxV, SCCDFS(next, goalSCCIdx));
		}
	}

	if (maxV == -1) return -1;
	else return SCCDP[sccIdx] = maxV + static_cast<int>(SCC[sccIdx].size());
}

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int V, E, S, T; cin >> V >> E >> S >> T;

	// 정점 : 1 ~ V
	// Edge 개수 : E개
	const int SIZE = V + 1;
	graph = vector(SIZE, vector<int>(0, 0));
	visited = vector(SIZE, 0);
	isFinish = vector(SIZE, 0);
	SCCIndex = vector(SIZE, 0); // SCCIndex = vector<int>(SIZE, 0); // 옛날
	SCC = vector<vector<int>>();

	for (int e{}; e < E; ++e) {
		int f, t; cin >> f >> t; // 방향성
		graph[f].push_back(t); // f -> t
	}

	// 첫 DFS -> Stack에 방문 순서대로 저장
	for (int i{ 1 }; i <= V; ++i) {
		if (!visited[i]) {
			DFS(i);
		}
	}

	// DAG
	SCCDP = vector<int>(static_cast<int>(SCC.size()), 0);
	SCCDFS(S, SCCIndex[T]);

	cout << SCCDP[SCCIndex[S]] << '\n'; // 미도달 = 0

	return 0;
}