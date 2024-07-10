/*
T(100)* { n ^ 2(250000) + m }
����, Ȯ���� ������ ã�� �� ���ٸ� "?"�� ��� => q�� size�� 2�� �̻� => ������ ���� �� ���� �����(�� ����������).
? ��� �����ؼ� ã�ƺ����ٰ� �ᱹ�� ���ٴ� ���� �˾������� ���� ����Ʈ�� ����! => �ð��� ���� �ɸ�.
�����Ϳ� �ϰ����� ��� ������ ���� �� ���� ��쿡�� "IMPOSSIBLE"�� ��� = > ����Ŭ�� ����� ���(��� ������ �� �湮���� �ʾҴµ� ť�� �� ���)

�ٷ� ���� ����� �ֲ��� �����߰��ϴ� ���� �ƴ�
�տ� �ִ� �ֵ�Ŵ� ��� �� �߰� + �ٲ� ������ �ٲ㼭 �߰� -> DAG �Ǵ�.
*/

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);

	int T; cin >> T;
	while (T--) {
		int n; cin >> n; // ���� ��
		vector<int> teams(n, 0);
		for (int& t : teams) cin >> t;

		vector<vector<int>> graph(n + 1); // 1 ~ n
		vector<vector<int>> adj(n + 1, vector<int>(n + 1, 0)); // 1 ~ n
		vector<int> indegrees(n + 1, 0); // 1 ~ n

		int m; cin >> m; // ������� ����� �ٲ� ���� ��
		for (int i{}; i < m; ++i) {
			int a, b; cin >> a >> b;
			adj[a][b] = 1;
			adj[b][a] = 1;
		}

		// Edge ����
		for (int i{}; i < n; ++i) {
			for (int j{ i + 1 }; j < n; ++j) {
				int first{ teams[i] }, second{ teams[j] }; // i -> j

				if (adj[first][second]) { // �ݴ�� �־�� ��
					swap(first, second);
				}

				graph[first].push_back(second);
				indegrees[second]++;
			}
		}
		queue<int> q;
		for (int i{ 1 }; i <= n; ++i) {
			if (indegrees[i] == 0) q.push(i);
		}

		vector<int> answer;
		answer.reserve(n);
		int chk = 0;
		while (!q.empty()) {
			int now = q.front(); q.pop();
			answer.push_back(now);

			for (int& next : graph[now]) {
				indegrees[next]--;
				if (indegrees[next] == 0) q.push(next);
				if (q.size() >= 2) chk = 2;
			}
			if (chk == 2) break;
		}

		if (answer.size() != n) chk = 1;

		if (chk == 2) cout << "?\n"; // ����� ������ ��� �̷� ���� ���� �� �ִ� ����� ���� ����.
		else if (chk == 1) cout << "IMPOSSIBLE\n";
		else {
			for (int& a : answer) cout << a << ' ';
			cout << '\n';
		}
	}
	
	return 0;
}