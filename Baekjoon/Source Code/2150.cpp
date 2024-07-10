// https://m.blog.naver.com/kks227/220802519976
// Tarjan's algorithm
// 3608KB, 24ms

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;
using Graph = vector<vector<int>>;
Graph graph;

vector<int> dfsn; // �湮 ���� ����
vector<int> sn; // sn[i] : ���� i�� ���� SCC ��ȣ
vector<bool> isFinish; // SCC�� ������ ������ ��� true

int dfsnIndex; // dfsn ī����
int SCCCnt; // SCC ����
vector<vector<int>> SCC; // SCC[i] : i��° SCC�� ���� V��.
stack<int> S;

constinit const int MAX = 10000;

/**
* �ڽ��� ����� ����
*/
int DFS(int curr) {
	dfsn[curr] = ++dfsnIndex; 
	S.push(curr);

	// curr���� �� �� �ִ� ���� �� dfsn �ּ� �� result�� ����
	int result = dfsn[curr];
	for (int& next : graph[curr]) {
		if (dfsn[next] == 0) {
			// ���� �湮���� ���� �̿� = �ڽ� -> �湮�ؼ� �ּҰ� ����
			result = min(result, DFS(next));
		}
		else if(!isFinish[next]) {
			// �湮�� ������ ���� SCC�� ��������� ���� �̿�(�� �����̶��� �� �� ����)
			result = min(result, dfsn[next]); // ������ ����� �� �̿�
		}
	}

	// �ڽ�, �ڽ��� �ڼյ��� ���� ������ ���� ���� ������ �ڽ��� ��� SCC ����
	if (result == dfsn[curr]) {
		// ���ÿ��� �ڽ��� ���� ������ pop
		vector<int> nowSCC;
		while (!S.empty()) {
			int t = S.top(); S.pop();
			nowSCC.push_back(t);
			isFinish[t] = true;
			sn[t] = SCCCnt;
			if (t == curr) break;
		}
		SCC.push_back(nowSCC);
		sort(begin(SCC[SCCCnt]), end(SCC[SCCCnt])); // �� ����� ���ؼ�
		++SCCCnt;
	}

	return result; // �ּ� dfsn ��ȯ
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	int V, E; cin >> V >> E;
	graph.assign(V + 1, vector<int>()); // 1 ~ V
	dfsn.assign(V + 1, 0);
	sn = vector<int>(V + 1, 0);
	isFinish.assign(V + 1, false);

	for (int e{}; e < E; ++e) {
		int f, t; cin >> f >> t; // ���⼺
		graph[f].push_back(t); // f -> t
	}

	// �� �������� DFS�ϸ鼭 SCC ����.
	// ���� �׷����� �ƴ� ���� �����Ƿ� �ݺ��� �ʿ�
	for (int v{1}; v <= V; ++v) {
		if (dfsn[v] == 0) { // ���� �̹湮
			DFS(v);
		}
	}
	sort(begin(SCC), end(SCC)); // �̰� ���� ������ ����..

	cout << SCCCnt << '\n'; // SCC ����
	// �� SCC ���
	for (vector<int>& row : SCC) {
		for (int& v : row) {
			cout << v << ' ';
		}
		cout << "-1\n";
	}

	return 0;
}