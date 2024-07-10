// ����
// https://m.blog.naver.com/kks227/220803009418
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

vector<vector<int>> graph, revGraph;

vector<int> finished, visited;

vector<int> SCCn; // SCCn[i] : i�� ���� scc ��ȣ
int SCCcnt;

stack<int> S;

struct Info {
	int SCCn;
	int nodeN;
	Info(int SCCn, int nodeN) : SCCn(SCCn), nodeN(nodeN) {}
	bool operator< (const Info& other) const {
		return SCCn < other.SCCn;
	}
};
vector<Info> infos;
// infos[i].SCCn : i�� ���� scc ��ȣ
// infos[i].nodeN = i : ���� ��ȣ - ����

void FillStack(int curr) {
	visited[curr] = 1;

	for (int& next : graph[curr]) {
		if (!visited[next]) {
			FillStack(next);
		}
	}

	S.push(curr);
}

void CalculateSCC(int curr) { // SCC ���ϴ� ���� ����
	visited[curr] = 1;
	SCCn[curr] = SCCcnt;
	infos[curr].SCCn = SCCcnt;

	for (int& next : revGraph[curr]) {
		if (!visited[next]) {
			CalculateSCC(next);
		}
	}

}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	int N, M;
	cin >> N >> M;
	graph = vector<vector<int>>(N * 2); // N = 3 -> 0 ~ 5
	revGraph = vector<vector<int>>(N * 2); // N = 3 -> 0 ~ 5

	for (int m{}; m < M; ++m) {
		int a, b; cin >> a >> b;
		// -1 -> 0, 1 -> 1
		// -2 -> 2, 2 -> 3
		// -3 -> 4, 3 -> 5
		if (a < 0) a = -2 * (a + 1);
		else a = 2 * a - 1;
		if (b < 0) b = -2 * (b + 1);
		else b = 2 * b - 1;
		// ���� ����
		int notA = (a & 1) == 0 ? a + 1 : a - 1;
		int notB = (b & 1) == 0 ? b + 1 : b - 1;
		graph[notA].push_back(b); // ~a -> b
		graph[notB].push_back(a); // ~b -> a
		revGraph[b].push_back(notA);
		revGraph[a].push_back(notB);
	}

	visited = vector<int>(N * 2, 0);
	SCCn = vector<int>(N * 2, 0);
	infos = vector<Info>(N * 2, Info(0, 0));
	finished = vector<int>(N * 2, 0);
	// SCC ã��
	for (int n{}; n < 2 * N; ++n) {
		infos[n].nodeN = n;
		if (visited[n] == 0) {
			FillStack(n);
		}
	}

	visited.assign(N * 2, 0);

	while (!S.empty()) {
		int now = S.top(); S.pop();

		if (!visited[now]) {
			CalculateSCC(now);
			++SCCcnt;
		}
	}

	sort(begin(infos), end(infos));
	// tarjan -> SCC ��ȣ�� ũ�� Ŭ���� DAG �󿡼� �տ� ��ġ��. (DFS ������ ������ ��� = ���� ����)

	bool chk = true;
	for (int n{}; n < N; ++n) {
		// 2n, 2n+1 ���� �ݴ�
		// ���� �ݴ� ������ ������ �ϳ��� �ϳ��� SCC�� ���ϸ� ����� ���� ���� �� ����.
		int curr = n << 1;
		if (SCCn[curr] == SCCn[curr + 1]) {
			chk = false;
			break;
		}
	}

	if (chk) {
		cout << "1\n";
		vector<int> answer(N, -1);
		for (int n{}; n < 2 * N; ++n) {
			// ���� �߰ߵǴ� ����(a)�� false�� ����!
			// ��, a -> b �� ��, a�� false�� ����
			int index = infos[n].nodeN;
			index >>= 1; // index�� �� ���� ���ο� ������� ��¥ index
			// infos[n].nodeN�� Ȧ�� => index�� true => �� false�� ����
			// infos[n].nodeN�� ¦�� => index�� false => �� true�� ����
			if (answer[index] == -1) answer[index] = !(infos[n].nodeN & 1);
		}

		for (int& an : answer) cout << an << ' ';
		cout << '\n';
	}
	else cout << "0\n";

	return 0;
}