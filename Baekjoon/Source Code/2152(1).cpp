#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;
vector<vector<int>> graph, revGraph;

vector<bool> visited; // �湮 ���� ����

vector<vector<int>> SCC; // SCC[i] : i��° SCC�� ���� V��.
vector<int> SCCIndex; // SCCIndex[i] : i��° ������ ���� SCC ��ȣ
vector<int> SCCDP; // SCCDP[i] : i��° SCC���� T�� ���ް����� ��� �湮������ �ִ� ���� ��
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
	int sccIdx = SCCIndex[curr]; // ���� ������ ���� scc ��ȣ
	if (sccIdx == goalSCCIdx) { // ����
		return SCCDP[sccIdx] = static_cast<int>(SCC[sccIdx].size());
	}

	int maxV{-1};
	for (int& sccV : SCC[sccIdx]) { // ��������
		for (int& next : graph[sccV]) { // sccV���� �� �� �ִ� next ����
			if (SCCIndex[next] == sccIdx) continue; // ����� ���� SCC

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

	// ���� : 1 ~ V
	// Edge ���� : E��
	const int SIZE = V + 1;
	cnt = 0;
	graph = vector(SIZE, vector<int>(0, 0));
	revGraph = vector(SIZE, vector<int>(0, 0));
	visited = vector(SIZE, false);
	SCCIndex = vector(SIZE, 0); // SCCIndex = vector<int>(SIZE, 0); // ����
	SCC = vector<vector<int>>();

	for (int e{}; e < E; ++e) {
		int f, t; cin >> f >> t; // ���⼺
		graph[f].push_back(t); // f -> t
		revGraph[t].push_back(f); // t -> f (��ġ �׷��� ����(���� �ٲٱ�))
	}

	// ù DFS -> Stack�� �湮 ������� ����
	for (int i{ 1 }; i <= V; ++i) {
		if (!visited[i]) {
			FillStack(i);
		}
	}

	fill(begin(visited), end(visited), false); // std::fill
	while (!s.empty()) {
		int now = s.top(); s.pop();
		if (!visited[now]) {
			vector<int> components; // SCC[index]�� �߰��� ������ ����
			CollectConnectedComponents(now, components);
			sort(begin(components), end(components));
			SCC.push_back(components);
			++cnt;
		}
	}

	// DAG
	SCCDP = vector<int>(cnt, 0);
	SCCDFS(S, SCCIndex[T]);

	cout << SCCDP[SCCIndex[S]] << '\n'; // �̵��� = 0

	return 0;
}