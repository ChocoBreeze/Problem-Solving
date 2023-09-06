// SCC에 속한 정점 찾기
// kosaraju
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

vector<vector<int>> graph, transposeGraph;
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

void CollectComponents(int curr, vector<int>& components, vector<int>& contains) {
	visited[curr] = true;
	components.push_back(curr);
	contains[curr] = 1;

	for (int& next : transposeGraph[curr]) {
		if (!visited[next]) {
			CollectComponents(next, components, contains);
		}
	}
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	while (1) {
		int n{}, m{};  // 노드의 수, 간선의 수
		cin >> n;
		if (n == 0) break;
		cin >> m;

		// graph.assign(n + 1, vector<int>()); // 1 ~ n
		graph = vector<vector<int>>(n + 1);
		transposeGraph = vector<vector<int>>(n + 1);

		for (int i{}; i < m; ++i) {
			int a, b; cin >> a >> b;
			graph[a].push_back(b); // directed
			transposeGraph[b].push_back(a);
		}
		visited = vector<int>(n + 1, 0);
		
		for (int v{ 1 }; v <= n; ++v) {
			if (!visited[v]) {
				FillStack(v);
			}
		}
		
		vector<int> ans;
		vector<int>(n + 1, 0).swap(visited);
		while (!S.empty()) {
			int now = S.top(); S.pop();

			if (!visited[now]) {
				vector<int> components;
				vector<int> contains(n+1, 0);
				CollectComponents(now, components, contains);

				bool chk = [&components, &contains]() -> bool {
					for (int& comp : components) {
						for (int& next : graph[comp]) {
							if (!contains[next]) {
								return false;
							}
						}
					}
					return true;
				} ();
				if (chk) {
					for (int& comp : components) {
						ans.push_back(comp);
					}
				}
			}
		}
		sort(begin(ans), end(ans));
		for (int& v : ans) cout << v << ' ';
		cout << '\n';
	}
	return 0;
}