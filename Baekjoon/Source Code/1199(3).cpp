// ����� �׷���(���� �׷���) -> ���Ϸ� ȸ�� - ������ Ȧ���� ������ 0���� �� ������.
// ���� ���� : https://m.blog.naver.com/kks227/220800097205
// https://justicehui.github.io/hard-algorithm/2019/01/04/euler/
// https://www.acmicpc.net/source/65454028
// ���̵�� : �������� next �������� ����ص���..(ó������ ��ȸ���� ����)

#include <iostream>
#include <vector>

using namespace std;

// adjacency matrix

vector<vector<int>> graph;
vector<int> nextStart;
int N{};

// ���Ϸ� ȸ�� ��¿� dfs
void Eulerian(int curr) {
	while (nextStart[curr] < N) {
		while (nextStart[curr] < N && graph[curr][nextStart[curr]] == 0) nextStart[curr]++;
		if (nextStart[curr] < N) {
			int& next = nextStart[curr];
			if (graph[curr][next]) {
				--graph[curr][next];
				--graph[next][curr];
				Eulerian(next);
			}
		}
	}
	cout << curr + 1 << ' ';
}

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	cin >> N;

	graph = vector<vector<int>>(N, vector<int>(N, 0)); // 0 ~ N - 1
	nextStart = vector<int>(N, 0);

	for (int i{}; i < N; ++i) {
		int degree{};
		for (int j{}; j < N; ++j) {
			int cnt{}; cin >> cnt; // ���� ����
			graph[i][j] = cnt;
			degree += cnt;
		}
		if (degree & 1) {
			// ���Ϸ� ȸ�� ���� ���� Ȯ�� - ������ Ȧ���� ������ �ϳ��� ������ �� ��
			cout << "-1\n";
			return 0;
		}
	}

	// ���Ϸ� ȸ�� ������. => ���(DFS)
	// �� ��쿣 �������� � �����̾ ���Ϸ� ȸ�� ���ϴ� ���� ������.
	// ��, �Է����� �־����� �׷����� ��� ����Ǿ� �ִ�. (������Ʈ �˻� ����)

	// ���Ϸ� ȸ��
	Eulerian(0);

	return 0;
}