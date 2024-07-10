// SCC�� ���� ���� ã��
// tarjan
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <unordered_set>

using namespace std;

vector<vector<int>> graph; // graph

vector<int> dfsn; // �湮 ���� ����
int dfsnIndex{};

vector<int> isFinish; // SCC�� ������ ��� true
stack<int> S;

vector<vector<int>> SCC; // SCC[i] : i��° SCC�� ���� V��.
vector<unordered_set<int>> SCCcontains; // SCCcontains[i] : i��° SCC�� ���� V�� ����.(O(1))

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
		else if (!isFinish[next]) {
			// �湮�� ������ ���� SCC�� ��������� ���� �̿�(�� �����̶��� �� �� ����)
			result = min(result, dfsn[next]); // ������ ����� �� �̿�
		}
	}

	// �ڽ�, �ڽ��� �ڼյ��� ���� ������ ���� ���� ������ �ڽ��� ��� SCC ����
	if (result == dfsn[curr]) {
		// ���ÿ��� �ڽ��� ���� ������ pop
		vector<int> nowSCC;
		unordered_set<int> nowSCCContains;
		while (!S.empty()) {
			int t = S.top(); S.pop();
			nowSCC.push_back(t);
			nowSCCContains.insert(t);
			isFinish[t] = 1;
			if (t == curr) break;
		}
		SCC.push_back(nowSCC);
		SCCcontains.push_back(nowSCCContains);
	}

	return result; // �ּ� dfsn ��ȯ
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	while (1) {
		int n{}, m{};  // ����� ��, ������ ��
		cin >> n;
		if (n == 0) break;
		cin >> m;

		vector<vector<int>>().swap(SCC); // empty swap
		vector<unordered_set<int>>().swap(SCCcontains); // empty swap

		// graph.assign(n + 1, vector<int>()); // 1 ~ n
		graph = vector<vector<int>>(n + 1);

		for (int i{}; i < m; ++i) {
			int a, b; cin >> a >> b;
			graph[a].push_back(b); // directed
		}
		dfsn = vector<int>(n + 1, 0);
		isFinish = vector<int>(n + 1, 0);
		
		for (int v{ 1 }; v <= n; ++v) {
			if (dfsn[v] == 0) {
				DFS(v);
			}
		}
		
		vector<int> ans;
		for (int i{}; i < static_cast<int>(SCC.size());++i) {
			bool chk = [i]() -> bool {
				for (int& elem : SCC[i]) {
					for (int& next : graph[elem]) {
						if (SCCcontains[i].find(next)==SCCcontains[i].end()) { // not found
							return false;
						}
					}
				}
				return true;
			} ();
			if (chk) {
				for (int& comp : SCC[i]) {
					ans.push_back(comp);
				}
			}
		}
		
		sort(begin(ans), end(ans));
		for (int& v : ans) cout << v << ' ';
		cout << '\n';
	}
	return 0;
}