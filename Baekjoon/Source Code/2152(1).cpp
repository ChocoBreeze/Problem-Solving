#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;
vector<vector<int>> graph, revGraph;

vector<bool> visited; // 방문 여부 저장

vector<vector<int>> SCC; // SCC[i] : i번째 SCC에 속한 V들.
vector<int> SCCIndex; // SCCIndex[i] : i번째 정점이 속한 SCC 번호
vector<int> SCCDP; // SCCDP[i] : i번째 SCC에서 T에 도달가능한 경우 방문가능한 최대 정점 수
int cnt;
stack<int> s;

void FillStack(int curr) {
	visited[curr] = true;
	for (int& next : graph[curr]) {
		if (!visited[next]) {
			FillStack(next);
		}
	}
	s.push(curr);
}

void CollectConnectedComponents(int curr, vector<int>& components) {
	visited[curr] = true;
	SCCIndex[curr] = cnt;
	components.push_back(curr);

	for (int& next : revGraph[curr]) {
		if (!visited[next]) {
			CollectConnectedComponents(next, components);
		}
	}
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
	cnt = 0;
	graph = vector(SIZE, vector<int>(0, 0));
	revGraph = vector(SIZE, vector<int>(0, 0));
	visited = vector(SIZE, false);
	SCCIndex = vector(SIZE, 0); // SCCIndex = vector<int>(SIZE, 0); // 옛날
	SCC = vector<vector<int>>();

	for (int e{}; e < E; ++e) {
		int f, t; cin >> f >> t; // 방향성
		graph[f].push_back(t); // f -> t
		revGraph[t].push_back(f); // t -> f (전치 그래프 생성(방향 바꾸기))
	}

	// 첫 DFS -> Stack에 방문 순서대로 저장
	for (int i{ 1 }; i <= V; ++i) {
		if (!visited[i]) {
			FillStack(i);
		}
	}

	fill(begin(visited), end(visited), false); // std::fill
	while (!s.empty()) {
		int now = s.top(); s.pop();
		if (!visited[now]) {
			vector<int> components; // SCC[index]에 추가될 정점들 벡터
			CollectConnectedComponents(now, components);
			sort(begin(components), end(components));
			SCC.push_back(components);
			++cnt;
		}
	}

	// DAG
	SCCDP = vector<int>(cnt, 0);
	SCCDFS(S, SCCIndex[T]);

	cout << SCCDP[SCCIndex[S]] << '\n'; // 미도달 = 0

	return 0;
}