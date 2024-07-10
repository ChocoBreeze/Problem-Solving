#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
vector<vector<int>> graph, DP;
vector<int> visited;

void Dfs(int curr) {
	DP[curr][1] = 1; // �ڱ� �ڽ��� �󸮾����
	for (int& next : graph[curr]) {
		if (visited[next]) continue;
		visited[next] = 1;
		Dfs(next);
		visited[next] = 0;
		DP[curr][0] += DP[next][1]; // �ڽ��� ������ �󸮾����.
		DP[curr][1] += min(DP[next][0], DP[next][1]); // �ڽ��� �󸮾�����̴� �ڽ��� ��� ����(�� �߿� ���� ��)
	}
}

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int N{}; cin >> N; // Ʈ�� ���� ��

	const int SIZE = N + 1;
	graph = vector<vector<int>>(SIZE);
	DP = vector<vector<int>>(SIZE, vector<int>(2, 0));

	visited.assign(SIZE, 0);

	for (int n{}; n < N - 1; ++n) {
		int a{}, b{}; cin >> a >> b;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}

	visited[1] = 1;
	Dfs(1);
	visited[1] = 0;

	cout << min(DP[1][0], DP[1][1]) << '\n';
	return 0;
}