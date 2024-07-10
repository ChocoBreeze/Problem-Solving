#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> graph;
vector<int> VisitOrder; // VisitOrder[i] : dfs tree���� i������ �湮 ���� ����
vector<bool> CutVertex; // CutVertex[i] : i�� �������� ��� true
int order = 0; // �湮 ���� ����
int ArticulationPointCnt{};

int dfs(int curr, int parent) {
	// ���� ����� low ���� �θ𿡰� ��ȯ�ؾ� ��.
	VisitOrder[curr] = ++order;
	int child_cnt{}, minOrder{ VisitOrder[curr] };

	// DFS Ʈ���󿡼� ���� ���� �������� �ƴ�.
	for (int& next : graph[curr]) {
		if (next == parent) continue; // �θ�
		if (VisitOrder[next]) { // �̹� �湮�� ��
			minOrder = min(minOrder, VisitOrder[next]);
		}
		else { // �̹湮��
			if (parent == 0) ++child_cnt;
			int low = dfs(next, curr);
			if (VisitOrder[curr] <= low && parent != 0) { // �ϳ��� �����ϴ� ��� curr�� ������(curr�� root�� �ƴ� ��)
				// curr�� ���ؼ��� �� �� �ִ� ����! -> curr�� ������
				if (CutVertex[curr] == false) {
					ArticulationPointCnt++; // false -> true�� ���� ī����
				}
				CutVertex[curr] = true;
			}
			minOrder = min(minOrder, low);
		}
	}
	// root node�� ��� �� �� �̻��� ���� �ٸ� BCC�� ����� ��쿡�� ������.
	if (parent == 0 && child_cnt >= 2) {
		CutVertex[curr] = true;
		ArticulationPointCnt++;
	}
	return minOrder;
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	int V, E; cin >> V >> E;
	graph = vector<vector<int>>(V + 1);
	VisitOrder = vector<int>(V + 1, 0); // �湮 ���� ����
	// VisitOrder.assign(V + 1, 0); 
	CutVertex = vector<bool>(V + 1, false); // �� ������ ������ ���� ����
	// CutVertex.assign(V + 1, false); 

	for (int e = 0; e < E; ++e) {
		int a, b; cin >> a >> b;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}

	// ���� �׷����� �ƴϹǷ� �� �������� dfs!
	for (int i = 1; i <= V; ++i) {
		if (!VisitOrder[i]) {
			dfs(i, 0);
		}
	}

	/*
	vector<int> answer;
	answer.reserve(V + 1);
	for (int i{1}; i <= V; ++i) { // ���߿� �����ϴ� �ͺ��� �̰� �� �� ��?
		if (CutVertex[i]) answer.push_back(i);
	}
	cout << answer.size() << "\n";
	for (int& a : answer) {
		cout << a << " ";
	}
	*/
	cout << ArticulationPointCnt << '\n';
	for (int i{ 1 }; i <= V; ++i) {
		if (CutVertex[i]) cout << i << ' ';
	}
	return 0;
}