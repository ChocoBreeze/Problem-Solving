// Kosaraju's algorithm
// 4420KB, 32ms

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;
using Graph = vector<vector<int>>;
Graph graph, transposeGraph;

vector<bool> visited; // �湮 ���� ����

vector<vector<int>> SCC; // SCC[i] : i��° SCC�� ���� V��.
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
		int f, t; cin >> f >> t; // ���⼺
		graph[f].push_back(t); // f -> t
		transposeGraph[t].push_back(f); // t -> f (��ġ �׷��� ����(���� �ٲٱ�))
	}

	// ù DFS -> Stack�� �湮 ������� ����
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

	// ���� ���� ���� SCC�� ���ؼ��� �� �ȿ� �����ִ� ���� ���� ������ ���� ��ȣ ������ ����Ѵ�.
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