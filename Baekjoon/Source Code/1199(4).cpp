// ����� �׷���(���� �׷���) -> ���Ϸ� ȸ�� - ������ Ȧ���� ������ 0���� �� ������.
// ���� ���� : https://m.blog.naver.com/kks227/220800097205
// https://www.acmicpc.net/source/65454028
// ���̵�� : �������� next �������� ����ص���..(ó������ ��ȸ���� ����)

// line 96 Ȯ��

#include <iostream>
#include <vector>

using namespace std;

// �� ���� ���̿� ������ ���� �� ���� �� �ִ�
struct Edge {
	int to, cnt, rev; // ������ ���ϴ� ����, ���� ����, �ݴ���� ���� �ε���
	Edge(int to, int cnt, int rev) : to(to), cnt(cnt), rev(rev) {}
};

vector<vector<Edge>> graph;
vector<int> degree, visited; // ������ ����, �湮 ����
vector<int> nextStart;

// ������Ʈ ���� �湮�ϴ� dfs
int dfs(int curr) {
	int ret = 1;
	visited[curr] = 1;
	for (auto& [to, cnt, rev] : graph[curr]) {
		if (!visited[to]) ret += dfs(to);
	}
	return ret;
}

// ���Ϸ� ȸ�� ��¿� dfs
void Eulerian(int curr) {
	int currSize = static_cast<int>(graph[curr].size());
	while (nextStart[curr] < currSize) {
		while (nextStart[curr] < currSize && graph[curr][nextStart[curr]].cnt == 0) nextStart[curr]++;
		// nextStart[curr] == currSize�� ���� �����ϱ�
		if (nextStart[curr] < currSize) {
			auto& [to, cnt, rev] = graph[curr][nextStart[curr]];
			// ������, ������ ���� �ϳ��� �����
			--cnt;
			--graph[to][rev].cnt;
			Eulerian(to); // dfs
		}
	}
	cout << curr + 1 << ' ';
}

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int N{}; cin >> N;

	graph = vector<vector<Edge>>(N); // 0 ~ N - 1
	degree = vector<int>(N, 0);
	visited = vector<int>(N, 0);
	nextStart = vector<int>(N, 0);

	for (int i{}; i < N; ++i) {
		for (int j{}; j < N; ++j) {
			int cnt{}; cin >> cnt; // ���� ����
			// ��Ī�� �׷���(j>i)�� ��쿡�� ó��(no self-loop)
			if (j > i && cnt) {
				int iRev = static_cast<int>(graph[i].size());
				int jRev = static_cast<int>(graph[j].size());
				graph[i].emplace_back(j, cnt, jRev);
				graph[j].emplace_back(i, cnt, iRev);
				degree[i] += cnt, degree[j] += cnt; // �� ������ ���� ����
			}
		}
	}

	// 1. ���Ϸ� ȸ�� ���� ���� Ȯ�� - ������ Ȧ���� ������ �ϳ��� ������ �� ��
	for (int& d : degree) {
		if (d & 1) {
			cout << "-1\n";
			return 0;
		}
	}

	// ���Ϸ� ȸ�� ������. => ���(DFS)
	// �� ��쿣 �������� � �����̾ ���Ϸ� ȸ�� ���ϴ� ���� ������.
	// �������� �� �ڵ�� �׷��� ū ���� �� ������..
	bool flag{};
	int start = -1;
	for (int n{}; n < N; ++n) {
		if (!visited[n]) {
			int cSize = dfs(n);
			if (cSize > 1) {
				if (flag) {
					// ũ�Ⱑ 2 �̻��� ������Ʈ�� 2�� �̻��̸� �Ұ���
					// ���� ������� ���� ũ�� 2 �̻��� ������Ʈ => ���Ϸ� ȸ�� ���� �� ����.
					// ũ�� 1��¥�� ���� �ϳ� �ִ� ���� ����
					cout << "-1\n";
					return 0;
				}
				else {
					// start = n; // �̰Ŵ� �� �ʿ��Ѱ���?
					flag = true;
				}
			}
		}
	}

	if (start == -1) start = 0;

	// ���Ϸ� ȸ�� ã�� ����
	Eulerian(start);

	return 0;
}