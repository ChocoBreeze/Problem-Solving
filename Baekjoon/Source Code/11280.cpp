// https://m.blog.naver.com/kks227/220803009418
// ����
// ���� ���� ó��
// SCC - �� ¥���ϱ� ��Ծ���..

#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

vector<vector<int>> graph;

vector<int> finished; // SCC ���� �Ϸ�

vector<int> orders; // �湮 ����
int order{};

vector<int> SCCnums; // SCCnums[i] : i�� ���� SCC ��ȣ
int SCCcnts{};

stack<int> S;

int DFS(int curr) {
	int result = orders[curr] = ++order;
	S.push(curr);

	for (int& next : graph[curr]) {
		if (orders[next] == 0) result = min(result, DFS(next)); // �湮�� �� ��
		else if (!finished[next]) result = min(result, orders[next]); // ���� SCC ������ �� ����
	}

	if (result == orders[curr]) {
		// ���� SCC �����ϴ� ���� ����
		while (1) {
			int t = S.top(); S.pop();
			finished[t] = 1;
			SCCnums[t] = SCCcnts;
			if (t == curr) break; // �ڽ��� ���� �� ����!
		}
		++SCCcnts;
	}

	return result;
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	int N, M; // ������ ����, ���� ����
	cin >> N >> M;
	graph = vector<vector<int>>(N * 2);
	// N = 3 -> 0 ~ 5

	for (int m{}; m < M; ++m) {
		int a, b;
		cin >> a >> b;
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
	}

	orders = vector<int>(N * 2, 0);
	SCCnums = vector<int>(N * 2, 0);
	finished = vector<int>(N * 2, 0);
	// SCC ã��
	for (int n{}; n < 2 * N; ++n) {
		if (orders[n] == 0) {
			DFS(n);
		}
	}

	bool chk = true;
	for (int n{}; n < N; ++n) {
		// 2n, 2n+1 ���� �ݴ�
		// ���� �ݴ� ������ ������ �ϳ��� �ϳ��� SCC�� ���ϸ� ����� ���� ���� �� ����.
		int curr = n << 1;
		if (SCCnums[curr] == SCCnums[curr + 1]) {
			chk = false;
			break;
		}
	}
	if (chk) cout << "1\n";
	else cout << "0\n";

	return 0;
}