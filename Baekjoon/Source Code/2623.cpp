// topological sort
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	int N, M; // ������ ��(����), ���� PD�� �� 
	// N�� 1�̻� 1,000������ �����̰�, M�� 1�̻� 100������ �����̴�.
	cin >> N >> M;
	vector<int> innode(N + 1, 0);
	vector<vector<int>> graph(N + 1);
	for (int m{}; m < M; ++m) {
		int in; cin >> in;
		int lastV{ -1 }; cin >> lastV;
		for (int i{1}; i < in; ++i) {
			int v; cin >> v;
			innode[v]++;
			graph[lastV].push_back(v);
			lastV = v;
		}
	}

	// ���� ������ ��쿡�� �ƹ��ų� �ϳ��� ��� �Ѵ�. 
	// ���� �����̰� ������ ���ϴ� ���� �Ұ����� ��쿡�� ù° �ٿ� 0�� ����Ѵ�.
	queue<int> q;
	for (int i{1}; i <= N; ++i) {
		if (innode[i] == 0) {
			q.push(i);
		}
	}
	vector<int> ans;
	ans.reserve(N);
	while (!q.empty()) {
		int now = q.front(); q.pop();
		// cout << now << '\n';
		ans.push_back(now);
		for (int& next : graph[now]) {
			innode[next]--;
			if (innode[next] == 0) q.push(next);
		}
	}

	if (static_cast<int>(ans.size()) != N) cout << "0\n";
	else {
		for (int& v : ans) cout << v << '\n';
	}

	return 0;
}