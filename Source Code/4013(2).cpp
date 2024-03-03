#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;
vector<vector<int>> graph;
vector<int> money; // Money[i] : ith ������ ������ �ִ� ��

vector<int> visited; // �湮 ���� ����
int dfsnIndex{};

vector<int> isFinish; // SCC�� ������ ��� true

vector<vector<int>> SCC; // SCC[i] : i��° SCC�� ���� V��.
vector<int> SCCIndex; // SCCIndex[i] : i��° ������ ���� SCC ��ȣ
int SCCCnt{};
stack<int> S;

vector<int> SCCDP, SCCMoney, SCCRestaurant, vRestaurant;
// SCCDP[i] : ith SCC ���� ����(��湮 ����)
// SCCMoney[i] : ith SCC���� �ִ�� ���� �� �ִ� ��.
// SCCRestaurant[i] : ith SCC�� �Ĵ��� �����ϴ���
// vRestaurant[i] : ���� i�� �Ĵ�����

int FindSCC(int curr) {
	visited[curr] = ++dfsnIndex;
	S.push(curr);

	// curr���� �� �� �ִ� ���� �� dfsn �ּ� ���� result�� ����
	int result = visited[curr];
	for (int& next : graph[curr]) {
		if (visited[next] == 0) { // �̹湮
			result = min(result, FindSCC(next));
		}
		else if (!isFinish[next]) {
			result = min(result, visited[next]);
		}
	}

	// �ڽ��� �ּ��� dfsn�� ��� -> SCC ����
	if (result == visited[curr]) {
		vector<int> nowSCC;
		while (!S.empty()) {
			int t = S.top(); S.pop();
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
	graph = vector(SIZE, vector<int>(0, 0));
	visited = vector(SIZE, 0);
	dfsnIndex = 0;
	isFinish = vector(SIZE, 0);
	SCCIndex = vector(SIZE, 0); // SCCIndex = vector<int>(SIZE, 0); // ����
	SCC = vector<vector<int>>();
	money = vector<int>(SIZE, 0);
	vRestaurant = vector<int>(SIZE, 0);

	for (int e{}; e < E; ++e) {
		int f, t; cin >> f >> t; // ���⼺
		graph[f].push_back(t); // f -> t
	}

	for (int v{ 1 }; v <= V; ++v) {
		if (!visited[v]) {
			FindSCC(v);
		}
		cin >> money[v]; // �Է±��� �ޱ�
	}

	int S, P; cin >> S >> P; // ������, �Ĵ� ����
	for (int p{}; p < P; ++p) {
		int in; cin >> in;
		vRestaurant[in] = 1;
	}

	SCCCnt = static_cast<int>(SCC.size());
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