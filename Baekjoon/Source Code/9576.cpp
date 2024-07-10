// �̺� ��Ī ����
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


struct SE {
	int s, e;
	SE(int s, int e) : s(s), e(e) {}
};
vector<SE> graph;
vector<int> visited, A, B;

bool Dfs(int curr) {
	visited[curr] = 1;

	for (int next{ graph[curr].s }; next <= graph[curr].e; ++next) {
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
	int T; cin >> T;
	while (T--) {
		int N, M; cin >> N >> M; // å�� N��, �кλ��� M��
		graph = vector<SE>(M, SE(0,0)); // 0 ~ N - 1

		for (SE& se : graph) { // 0 ~ M - 1
			cin >> se.s >> se.e;
			se.s--, se.e--;
		}

		int answer{};
		A = vector<int>(M, -1); // �кλ�
		B = vector<int>(N, -1); // å

		for (int m{}; m < M; ++m) {
			// ���� ��Ī���� ���� �׷� A ������ ���� ��Ī �õ�
			if (A[m] == -1) {
				vector<int>(M, 0).swap(visited); // visited �迭 �ʱ�ȭ
				if (Dfs(m)) ++answer;
			}
		}
		cout << answer << '\n';
	}

	return 0;
}