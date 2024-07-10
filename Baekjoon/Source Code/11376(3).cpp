// < Hopcroft-Karp : O(E * sqrt(V)) >
// 10244KB, 1132ms

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
	cin >> N >> M; // 직원의 수, 일의 수
	// 직원 당 일 2개 가능. => N 2배
	N <<= 1;
	adj = vector(N, vector<int>());
	level = vector(N, 0);
	used = vector(N, false);

	int befN = N >> 1; // before N
	for (int n{}; n < befN; ++n) {
		int S{}; cin >> S; // 할 수 있는 일의 개수
		for (int i{}; i < S; ++i) {
			int s{}; cin >> s; --s;
			int first{ n << 1 }, second{ (n << 1) + 1 };
			adj[first].push_back(s);
			adj[second].push_back(s);
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
	return 0;
}