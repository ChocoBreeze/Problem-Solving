// 선택된 간선의 수가 가치가 되기 때문에 이분 매칭으로 구할 수 있음.
// 2444KB, 40ms
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;
constinit const int INF = 1 << 30;

int N, M;
vector<bool> used;
vector<vector<int>> adj;
vector<int> A, B, level;

void bfs() {
	queue<int> q;
	// 매칭에 안 속한 A 그룹의 정점만 레벨 0인 채로 시작
	for (int n{}; n < N; ++n) {
		if (!used[n]) {
			level[n] = 0;
			q.push(n);
		}
		else level[n] = INF;
	}

	// A 그룹의 정점에 0, 1, 2, 3, ... 의 레벨을 매김
	while (!q.empty()) {
		int a{ q.front() }; q.pop();
		for (int& b : adj[a]) {
			if (B[b] != -1 && level[B[b]] == INF) {
				level[B[b]] = level[a] + 1;
				q.push(B[b]);
			}
		}
	}
}

bool dfs(int a) {
	for (int& b : adj[a]) {
		if (B[b] == -1 || (level[B[b]] == level[a] + 1 && dfs(B[b]))) { 
			used[a] = true;
			A[a] = b;
			B[b] = a;
			return true;
		}
	}
	return false;
}

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int T{}; cin >> T;
	while (T--) {
		cin >> N >> M; // 노드의 수(0 ~ N - 1), 단방향 링크의 수
		adj = vector(N, vector<int>());
		level = vector(N, 0);
		used = vector(N, false);
		for (int m{}; m < M; ++m) {
			int a{}, b{}; cin >> a >> b;
			adj[a].push_back(b);
		}

		int match{};
		A = vector(N, -1);
		B = vector(N, -1);

		while (1) {
			bfs(); // level graph

			int flow{};
			for (int n{}; n < N; ++n) {
				if (!used[n] && dfs(n)) ++flow;
			}

			if (flow == 0) break; // not find augmenting path

			match += flow;
		}
		cout << match << '\n';
	}

	return 0;
}