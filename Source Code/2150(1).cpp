// Kosaraju's algorithm
// 4420KB, 32ms

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;
using Graph = vector<vector<int>>;
Graph graph, transposeGraph;

vector<bool> visited; // 방문 여부 저장

vector<vector<int>> SCC; // SCC[i] : i번째 SCC에 속한 V들.
stack<int> S;

constinit const int MAX = 10000;

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
	components.push_back(curr);

	for (int& next : transposeGraph[curr]) {
		if (!visited[next]) {
			CollectConnectedComponents(next, components);
		}
	}
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	int V, E; cin >> V >> E;
	graph.assign(V + 1, vector<int>()); // 1 ~ V
	transposeGraph.assign(V + 1, {}); // 1 ~ V
	visited.assign(V + 1, false);

	for (int e{}; e < E; ++e) {
		int f, t; cin >> f >> t; // 방향성
		graph[f].push_back(t); // f -> t
		transposeGraph[t].push_back(f); // t -> f (전치 그래프 생성(방향 바꾸기))
	}

	// 첫 DFS -> Stack에 방문 순서대로 저장
	for (int i = 1; i <= V; i++)
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
		}
	}

	// 또한 여러 개의 SCC에 대해서는 그 안에 속해있는 가장 작은 정점의 정점 번호 순으로 출력한다.
	sort(begin(SCC), end(SCC)); 

	cout << SCC.size() << '\n';
	for (auto& row : SCC) {
		for (int& v : row) {
			cout << v << ' ';
		}
		cout << "-1\n";
	}

	return 0;
}