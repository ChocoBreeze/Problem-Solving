// < Hopcroft-Karp : O(E * sqrt(V)) >
// 6132KB, 176ms

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

// A 그룹의 각 정점에 레벨을 매김
void bfs() {
	queue<int> q;
	for (int i{}; i < N; ++i) {
		if (!used[i]) {
			level[i] = 0;
			q.push(i);
		}
		else level[i] = INF;
	}

	while (!q.empty()) {
		int a = q.front(); q.pop();
		for (int& b : adj[a]) {
			if (B[b] != -1 && level[B[b]] == INF) {
				level[B[b]] = level[a] + 1;
				q.push(B[b]);
			}
		}
	}
}

// 새 매칭을 찾으면 true
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
		cin >> N >> M; // 책, 학부생 (책 한권당 학부생 한 명)
		adj = vector(N, vector<int>());
		level = vector(N, 0);
		used = vector(N, false);
		for (int m{}; m < M; ++m) { // 학부생
			int a{}, b{}; cin >> a >> b; // [a, b]
			--a, --b;
			for (int i{ a }; i <= b; ++i) {
				adj[i].push_back(m);
			}
		}
		// Hopcroft-Karp
		int match{};
		A = vector(N, -1);
		B = vector(M, -1);

		while (1) {
			bfs();

			int flow{};
			for (int n{}; n < N; ++n) {
				if (!used[n] && dfs(n)) ++flow;
			}

			if (flow == 0) break;

			match += flow;
		}
		cout << match << '\n';
	}

	return 0;
}