// Bipartite Matching
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> graph;
vector<int> A, B, visited;

bool DFS(int curr) {
	visited[curr] = 1;

	for (int& next : graph[curr]) {
		// ������ �Ǿ� ���� �ʰų� 
		// ��Ī�Ǿ� �ִ� ���� �ٸ� ������ ��Ī��ų �� ������
		if (B[next] == 0 || (!visited[B[next]] && DFS(B[next]))) { // DFS(next) �ƴ�!
			A[curr] = next;
			B[next] = curr;
			return true;
		}
	}
	return false;
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	int N, M; cin >> N >> M; // ���� 1 ~ N, �� 1 ~ M
	// �� ������ �ִ� �� ���� ���� �� �� �ְ� => ���� ������ 2�� ������
	const int WORKERNUM = (N << 1) + 1;
	// 1 -> 1, 2
	// n -> 2n - 1, 2n

	graph = vector<vector<int>>(WORKERNUM);
	for (int n{ 1 }; n <= N; ++n) {
		int cnt{}; cin >> cnt;
		for (int i{}; i < cnt; ++i) {
			int work{}; cin >> work;
			int first{ (n << 1) - 1 }, second{ n << 1 };
			graph[first].push_back(work);
			graph[second].push_back(work);
		}
	}

	int match{};
	A = vector<int>(WORKERNUM, 0);
	B = vector<int>(M + 1, 0);
	for (int n{ 1 }; n < WORKERNUM; ++n) {
		if (!A[n]) {
			visited.assign(WORKERNUM, 0);
			if (DFS(n)) ++match;
		}
	}

	cout << match << '\n';

	return 0;
}