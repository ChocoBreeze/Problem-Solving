// Kosaraju's algorithm

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;
vector<vector<int>> graph, revGraph;

vector<bool> visited; // �湮 ���� ����

vector<vector<int>> SCC; // SCC[i] : i��° SCC�� ���� V��.
vector<int> SCCIndex; // SCCIndex[i] : i��° ������ ���� SCC ��ȣ
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
		SCCIndex = vector(V, 0); // SCCIndex = vector<int>(V, 0); // ����
		SCC = vector<vector<int>>();

		for (int e{}; e < E; ++e) {
			int f, t; cin >> f >> t; // ���⼺
			graph[f].push_back(t); // f -> t
			revGraph[t].push_back(f); // t -> f (��ġ �׷��� ����(���� �ٲٱ�))
		}

		// ù DFS -> Stack�� �湮 ������� ����
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

		// index : SCC ����
		vector<int> SCCIndegree(index, 0);
		for (int sccidx{}; sccidx < index; ++sccidx) { // scc����
			for (int& sccV : SCC[sccidx]) { // sccidx��° SCC�� ���� �����鸶��
				for (int& next : graph[sccV]) {
					if (SCCIndex[next] == sccidx) continue; // ����� ���� SCC
					else SCCIndegree[SCCIndex[next]]++;
				}
			}
		}

		// Indegree�� 0���� SCC�� 2�� �̻� �ִ��� Ȯ��
		int answerSCC{ -1 };
		for (int sccidx{}; sccidx < index; ++sccidx) {
			if (SCCIndegree[sccidx] == 0) {
				if (answerSCC == -1) answerSCC = sccidx; // ù �߰� �� index ����
				else {
					answerSCC = -2; // �� ��° �߰� ��!
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