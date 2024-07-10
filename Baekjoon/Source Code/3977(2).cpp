// tarjan
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

vector<vector<int>> graph; // graph

vector<int> visited; // �湮 ���� ����
int dfsnIndex{};

vector<int> isFinish; // SCC�� ������ ��� true

vector<vector<int>> SCC; // SCC[i] : i��° SCC�� ���� V��.
vector<int> SCCIndex; // SCCIndex[i] : i��° ������ ���� SCC ��ȣ

stack<int> S;

int DFS(int curr) {
	visited[curr] = ++dfsnIndex;
	S.push(curr);

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

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int T{}; cin >> T;

	while(T--) {
		int N, M; cin >> N >> M; // ���� ��, ���� ��
		
		// ���� : 1 ~ N
		graph = vector<vector<int>>(N);
		visited = vector<int>(N, 0);
		dfsnIndex = 0;
		isFinish = vector<int>(N, 0);
		vector<vector<int>>().swap(SCC); // swap empty
		SCCIndex = vector<int>(N, 0);

		for (int m{}; m < M; ++m) {
			int a, b; cin >> a >> b;
			graph[a].push_back(b);
		}
		
		for (int n{}; n < N; ++n) {
			if (!visited[n]) {
				DFS(n);
			}
		}

		// SCCNum : SCC ����
		int SCCNum = static_cast<int>(SCC.size());
		vector<int> SCCIndegree(SCCNum, 0);
		for (int sccidx{}; sccidx < SCCNum; ++sccidx) { // scc����
			for (int& sccV : SCC[sccidx]) { // sccidx��° SCC�� ���� �����鸶��
				for (int& next : graph[sccV]) {
					if (SCCIndex[next] == sccidx) continue; // ����� ���� SCC
					else SCCIndegree[SCCIndex[next]]++;
				}
			}
		}

		// Indegree�� 0���� SCC�� 2�� �̻� �ִ��� Ȯ��
		int answerSCC{ -1 };
		for (int sccidx{}; sccidx < SCCNum; ++sccidx) {
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