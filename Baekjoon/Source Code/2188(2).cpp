// https://m.blog.naver.com/kks227/220807541506
// �̺� ��Ī ����
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> graph;
vector<int> visited, A, B;

bool Dfs(int curr) {
	visited[curr] = 1;

	for (int& next : graph[curr]) {
		// �ݴ����� ��Ī���� �ʰų� (B[next] == -1)
		// ��Ī�Ǿ� �־����� ���� ��Ī�Ǿ� �ִ� ������ �ٸ� ������ ��Ī��ų �� ������ ����
		if (B[next] == -1 || (!visited[B[next]] && Dfs(B[next]))) {
			A[curr] = next;
			B[next] = curr;
			return true;
		}
	}
	// ��Ī ����
	return false;
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	int N, M; cin >> N >> M;

	graph = vector<vector<int>>(N); // 0 ~ N - 1 (�� -> ���)
	for (int n{}; n < N; ++n) { 
		int S; cin >> S;
		for (int s{}; s < S; ++s) {
			int k; cin >> k;
			graph[n].push_back(k - 1);
		}
	}

	int answer{};
	A = vector<int>(N, -1); // ��
	B = vector<int>(M, -1); // ��� (N���� ������ out of bounds)

	for (int n{}; n < N; ++n) {
		// ���� ��Ī���� ���� �׷� A ������ ���� ��Ī �õ�
		if (A[n] == -1) {
			vector<int>(N, 0).swap(visited); // visited �迭 �ʱ�ȭ
			if (Dfs(n)) ++answer;
		}
	}
	cout << answer << '\n';

	return 0;
}