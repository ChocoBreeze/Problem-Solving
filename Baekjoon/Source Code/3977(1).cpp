// Kosaraju's algorithm

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;
vector<vector<int>> graph, revGraph;

vector<bool> visited; // 방문 여부 저장

vector<vector<int>> SCC; // SCC[i] : i번째 SCC에 속한 V들.
vector<int> SCCIndex; // SCCIndex[i] : i번째 정점이 속한 SCC 번호
int index;
stack<int> S;

void FillStack(int curr) {
	visited[curr] = true;

	for (int& next : graph[curr]) {
		if (!visited[next]) {
			FillStack(next);
		}
	}

	S.push(curr);
}

void CollectConnectedComponents(int curr, vector<int>& components) {
	visited[curr] = true;
	SCCIndex[curr] = index;
	components.push_back(curr);

	for (int& next : revGraph[curr]) {
		if (!visited[next]) {
			CollectConnectedComponents(next, components);
		}
	}
}

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int T{}; cin >> T;
	while (T--) {
		int V, E; cin >> V >> E;

		index = 0;
		graph = vector(V, vector<int>(0, 0));
		revGraph = vector(V, vector<int>(0, 0));
		visited = vector(V, false);
		SCCIndex = vector(V, 0); // SCCIndex = vector<int>(V, 0); // 옛날
		SCC = vector<vector<int>>();

		for (int e{}; e < E; ++e) {
			int f, t; cin >> f >> t; // 방향성
			graph[f].push_back(t); // f -> t
			revGraph[t].push_back(f); // t -> f (전치 그래프 생성(방향 바꾸기))
		}

		// 첫 DFS -> Stack에 방문 순서대로 저장
		for (int i{}; i < V; ++i)
		{
			if (!visited[i])
			{
				FillStack(i);
			}
		}

		fill(begin(visited), end(visited), false); // std::fill

		while (!S.empty()) {
			int now = S.top(); S.pop();
			if (!visited[now]) {
				vector<int> components;
				CollectConnectedComponents(now, components);
				sort(begin(components), end(components));
				SCC.push_back(components);
				++index;
			}
		}

		// index : SCC 개수
		vector<int> SCCIndegree(index, 0);
		for (int sccidx{}; sccidx < index; ++sccidx) { // scc마다
			for (int& sccV : SCC[sccidx]) { // sccidx번째 SCC에 속한 정점들마다
				for (int& next : graph[sccV]) {
					if (SCCIndex[next] == sccidx) continue; // 현재랑 같은 SCC
					else SCCIndegree[SCCIndex[next]]++;
				}
			}
		}

		// Indegree가 0개인 SCC가 2개 이상 있는지 확인
		int answerSCC{ -1 };
		for (int sccidx{}; sccidx < index; ++sccidx) {
			if (SCCIndegree[sccidx] == 0) {
				if (answerSCC == -1) answerSCC = sccidx; // 첫 발견 시 index 갱신
				else {
					answerSCC = -2; // 두 번째 발견 시!
					break;
				}
			}
		}

		if (answerSCC == -2) cout << "Confused\n";
		else {
			for (int& v : SCC[answerSCC]) cout << v << '\n';
		}
		cout << '\n';

	}
	return 0;
}