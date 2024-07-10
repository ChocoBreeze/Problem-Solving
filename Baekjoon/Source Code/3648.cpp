// �ǽ� ���� ����� = clause
// ����̴� ������ �����ϱ� : ���� clause ���� (1 V 1)
// 2-SAT
// kosaraju

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

vector<vector<int>> graph, revGraph;

vector<int> visited, sccN;
int sccNum;

stack<int> S;

void FillStack(int curr) {
	visited[curr] = 1;
	for (int& next : graph[curr]) {
		if (!visited[next]) FillStack(next);
	}
	S.push(curr);
}

void CalculateSCC(int curr) {
	visited[curr] = 1;
	sccN[curr] = sccNum;
	for (int& next : revGraph[curr]) {
		if (!visited[next]) CalculateSCC(next);
	}
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);

	while (1) {
		int n, m; cin >> n >> m; // �������� ��, �ɻ������� ��
		if (cin.eof()) break;
		// �������� ��ȣ : 1 ~ n

		const int vertexN = n << 1;
		sccNum = 0; // �̰� ���Ծ��µ� �����..
		stack<int>().swap(S); // swap empty
		graph = vector<vector<int>>(vertexN); // n <= 1000
		revGraph = vector<vector<int>>(vertexN); // n <= 1000
		sccN = vector<int>(vertexN, 0);

		for (int i{}; i < m; ++i) {
			// -2 => 2 ( a => -2a - 2)
			// 2 => 3 (a => 2a - 1)
			int a{}, b{}; cin >> a >> b;
			a = (a < 0) ? -2 * a - 2 : 2 * a - 1;
			b = (b < 0) ? -2 * b - 2 : 2 * b - 1;
			int revA{ a ^ 1 }, revB{ b ^ 1 };
			graph[revA].push_back(b); // ~a -> b
			graph[revB].push_back(a); // ~b -> a
			revGraph[b].push_back(revA);
			revGraph[a].push_back(revB);
		}
		// ����̴� �׻� ����. (1 v 1)�� ���� �����
		// ��, ~1 -> 1
		graph[0].push_back(1);
		revGraph[1].push_back(0); // �̰ŵ� ���Ծ��µ�?..

		visited.assign(vertexN, 0);
		for (int v{}; v < vertexN; ++v) {
			if (!visited[v]) {
				FillStack(v);
			}
		}

		visited.assign(vertexN, 0);
		while (!S.empty()) {
			int now = S.top(); S.pop();
			if (!visited[now]) { // �־�� ��
				CalculateSCC(now);
				++sccNum;
			}
		}

		bool chk = [&vertexN]() -> bool {
			for (int v{}; v < vertexN; v += 2) {
				int first = v, second = v + 1;
				if (sccN[first] == sccN[second]) return false;
			}
			return true;
		} ();
		if (chk) cout << "yes\n";
		else cout << "no\n";
	}

	return 0;
}