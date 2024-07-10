// 4148KB, 72ms
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
	int K{};
	cin >> N >> M >> K; // 직원의 수, 일의 수, 일을 2개할 수 있는 직원의 수
	adj = vector(N, vector<int>());

	for (int n{}; n < N; ++n) {
		int S{}; cin >> S; // 할 수 있는 일의 개수
		for (int i{}; i < S; ++i) {
			int s{}; cin >> s; --s;
			adj[n].push_back(s);
		}
	}

	// Hopcroft-Karp
	int answer{};
	// 이분 매칭 2번 진행(그냥 이분 매칭 + K개만 뽑는 이분매칭)
	B = vector(M, -1);
	for (int t{}; t < 2; ++t) {
		// level, used도 초기화해야 함..
		A = vector(N, -1);
		level = vector(N, 0);
		used = vector(N, false);
		int match{}; // 현재 이분 매칭에서 match 개수
		while (1) {
			bfs();

			int flow{};
			for (int n{}; n < N; ++n) {
				if (!used[n] && dfs(n)) {
					++answer;
					++match;
					++flow;
					if (t == 1 && match == K) break;
				}
			}
			if (flow == 0) break;
			// match += flow;
			if (t == 1 && match == K) break;
		}
	}
	cout << answer << '\n';
	return 0;
}