#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;
vector<vector<int>> graph;

vector<int> visited; // �湮 ���� ����
int dfsnIndex{};

vector<int> isFinish; // SCC�� ������ ��� true

vector<vector<int>> SCC; // SCC[i] : i��° SCC�� ���� V��.
vector<int> SCCIndex; // SCCIndex[i] : i��° ������ ���� SCC ��ȣ
vector<int> SCCDP; // SCCDP[i] : i��° SCC���� T�� ���ް����� ��� �湮������ �ִ� ���� ��
stack<int> s;

int DFS(int curr) {
	visited[curr] = ++dfsnIndex;
	s.push(curr);

	// curr���� �� �� �ִ� ���� �� dfsn �ּ� ���� result�� ����
	int result = visited[curr];
	for (int& next : graph[curr]) {
		if (visited[next] == 0) { // �̹湮
			result = min(result, DFS(next));
		}
		else if (!isFinish[next]) {
			result = min(result, visited[next]);
		}
	}

	// �ڽ��� �ּ��� dfsn�� ��� -> SCC ����
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
	graph = vector(SIZE, vector<int>(0, 0));
	visited = vector(SIZE, 0);
	isFinish = vector(SIZE, 0);
	SCCIndex = vector(SIZE, 0); // SCCIndex = vector<int>(SIZE, 0); // ����
	SCC = vector<vector<int>>();

	for (int e{}; e < E; ++e) {
		int f, t; cin >> f >> t; // ���⼺
		graph[f].push_back(t); // f -> t
	}

	// ù DFS -> Stack�� �湮 ������� ����
	for (int i{ 1 }; i <= V; ++i) {
		if (!visited[i]) {
			DFS(i);
		}
	}

	// DAG
	SCCDP = vector<int>(static_cast<int>(SCC.size()), 0);
	SCCDFS(S, SCCIndex[T]);

	cout << SCCDP[SCCIndex[S]] << '\n'; // �̵��� = 0

	return 0;
}