#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;
vector<vector<int>> graph, revGraph;
vector<int> money; // Money[i] : ith ������ ������ �ִ� ��

vector<bool> visited; // �湮 ���� ����

vector<vector<int>> SCC; // SCC[i] : i��° SCC�� ���� V��.
vector<int> SCCIndex; // SCCIndex[i] : i��° ������ ���� SCC ��ȣ
int SCCCnt{};
stack<int> S;

vector<int> SCCDP, SCCMoney, SCCRestaurant, vRestaurant;
// SCCDP[i] : ith SCC ���� ����(��湮 ����)
// SCCMoney[i] : ith SCC���� �ִ�� ���� �� �ִ� ��.
// SCCRestaurant[i] : ith SCC�� �Ĵ��� �����ϴ���
// vRestaurant[i] : ���� i�� �Ĵ�����

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
	SCCIndex[curr] = SCCCnt;
	// SCCMoney[index] += money[curr];
	components.push_back(curr);

	for (int& next : revGraph[curr]) {
		if (!visited[next]) {
			CollectConnectedComponents(next, components);
		}
	}
}

int DFS(int curr) {
	int currSCC = SCCIndex[curr];

	bool isTerminal{true}; // �� �̻� �� �� ���� ������ ���
	int maxRet{-2}; // ���� SCC���� ���� �� �ִ� �ִ� ��
	for (int& v : SCC[currSCC]) {
		for (int& next : graph[v]) {
			int nextSCC = SCCIndex[next];
			if (currSCC == nextSCC) continue; // same SCC
			isTerminal = false; // �ٸ� SCC�� �̵� ����
			if (SCCDP[nextSCC] == -2) maxRet = max(maxRet, DFS(next));
			// else if (SCCDP[nextSCC] == -1) maxRet = max(max; // next�� ���ļ� �� �� �ִ� �Ĵ��� ���� ��
			else maxRet = max(maxRet, SCCDP[nextSCC]);
		}
	}

	if (isTerminal) {
		if (SCCRestaurant[currSCC]) return SCCDP[currSCC] = SCCMoney[currSCC];
		return SCCDP[currSCC] = -1; // ���Ⱑ �Ĵ��� �ƴ�.
	}
	else {
		if (maxRet == -1) {
			// �� �� �ִ� SCC �߿� Restaurant�� �� ���� ����.
			if (SCCRestaurant[currSCC]) return SCCDP[currSCC] = SCCMoney[currSCC]; // ���� SCC�� �Ĵ��� ���
			else return SCCDP[currSCC] = -1;
		}
		else {
			// �� �� �ִ� SCC �߿� �Ĵ��� �����Ѵ�.
			return SCCDP[currSCC] = SCCMoney[currSCC] + maxRet;
		}
	}
}

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int V, E; cin >> V >> E;

	// ���� : 1 ~ V
	// Edge ���� : E��
	const int SIZE = V + 1;
	SCCCnt = 0;
	graph = vector(SIZE, vector<int>(0, 0));
	revGraph = vector(SIZE, vector<int>(0, 0));
	visited = vector(SIZE, false);
	SCCIndex = vector(SIZE, 0); // SCCIndex = vector<int>(SIZE, 0); // ����
	SCC = vector<vector<int>>();
	money = vector<int>(SIZE, 0);
	vRestaurant = vector<int>(SIZE, 0);

	for (int e{}; e < E; ++e) {
		int f, t; cin >> f >> t; // ���⼺
		graph[f].push_back(t); // f -> t
		revGraph[t].push_back(f); // t -> f (��ġ �׷��� ����(���� �ٲٱ�))
	}

	// ù DFS -> Stack�� �湮 ������� ����
	for (int v{ 1 }; v <= V; ++v) {
		if (!visited[v]) {
			FillStack(v);
		}
		cin >> money[v]; // �Է±��� �ޱ�
	}

	// �� ��° DFS -> SCC �����
	fill(begin(visited), end(visited), false); // std::fill
	while (!S.empty()) {
		int now = S.top(); S.pop();
		if (!visited[now]) {
			vector<int> components; // SCC[index]�� �߰��� ������ ����
			CollectConnectedComponents(now, components);
			sort(begin(components), end(components));
			SCC.push_back(components);
			++SCCCnt;
		}
	}

	int S, P; cin >> S >> P; // ������, �Ĵ� ����
	for (int p{}; p < P; ++p) {
		int in; cin >> in;
		vRestaurant[in] = 1;
	}

	SCCDP = vector<int>(SCCCnt, -2); // �ݾ��� 0���� �ȴ�..
	SCCMoney = vector<int>(SCCCnt, 0);
	SCCRestaurant = vector<int>(SCCCnt, 0);
	for (int i{}; i < SCCCnt; ++i) {
		for (int& v : SCC[i]) {
			SCCMoney[i] += money[v]; // �ش� SCC�� ���ϴ� �� ����
			SCCRestaurant[i] |= vRestaurant[v]; // �ϳ��� �Ĵ��� �ִٸ�
		}
	}

	int answer = DFS(S);
	cout << answer << '\n';

	return 0;
}