// ����� �׷���(���� �׷���) -> ���Ϸ� ȸ�� - ������ Ȧ���� ������ 0���� �� ������.
// ���� ���� : https://m.blog.naver.com/kks227/220800097205

#include <iostream>
#include <vector>

using namespace std;

// �� ���� ���̿� ������ ���� �� ���� �� �ִ�
struct Edge {
	int to, cnt, rev; // ������ ���ϴ� ����, ���� ����, �ݴ���� ���� �ε���
	Edge(int to, int cnt, int rev) : to(to), cnt(cnt), rev(rev) {}
};

vector<vector<Edge>> graph;
vector<int> degree; // ������ ����

// ���Ϸ� ȸ�� ��¿� dfs
void Eulerian(int curr) {
	for (auto& [to, cnt, rev] : graph[curr]) {
		if (cnt > 0) {
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

	for (int i{}; i < N; ++i) {
		for (int j{}; j < N; ++j) {
			int cnt{}; cin >> cnt; // ���� ����
			// ��Ī�� �׷���(j>i)�� ��쿡�� ó��(no self-loop)
			if (j > i && cnt) {
				int iRev = static_cast<int>(graph[i].size());
				int jRev = static_cast<int>(graph[j].size());
				graph[i].emplace_back(j, cnt, jRev);
				graph[j].emplace_back(i, cnt, iRev);
				degree[i]+=cnt, degree[j]+=cnt; // �� ������ ���� ����
			}
		}
		if (degree[i] & 1) {
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