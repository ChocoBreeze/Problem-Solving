// sparse table 이용
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	int T, N;
	cin >> T;
	for (int t = 0; t < T; ++t) {
		cin >> N;
		int a, b;
		vector<vector<int>> Edges(N + 1);
		vector<int> e_count(N+1);
		for (int i = 1; i < N; ++i) {
			cin >> a >> b;
			Edges[a].push_back(b);
			e_count[b]++;
		}
		int root = 0;
		for (int i = 1; i <= N; ++i) {
			if (!e_count[i]) root = i;
		}
		vector<int> depth(N + 1, -1);
		queue<int> Q;
		// 노드의 최대 개수 = 10000 ( 2^14 = 16384)
		vector<vector<int>> S(15, vector<int>(N + 1, 0)); // sparse table
		Q.push(root);
		depth[root] = 0;
		while (!Q.empty()) {
			int now = Q.front();
			Q.pop();
			for (auto& i : Edges[now]) {
				if (depth[i] == -1) {
					Q.push(i);
					depth[i] = depth[now] + 1;
					S[0][i] = now;
				}
			}
		}
		for (int i = 1; i < 15; ++i) {
			for (int j = 1; j <= N; ++j) {
				S[i][j] = S[i - 1][S[i - 1][j]];
			}
		}
		cin >> a >> b;
		if (depth[a] > depth[b]) swap(a, b);
		int diff = depth[b] - depth[a];
		for (int i = 0; diff > 0; ++i ) {
			if (diff & 1) b = S[i][b];
			diff >>= 1;
		}
		while (a != b) {
			int i;
			for (i = 0; i < 15; ++i) {
				if (S[i][a] == S[i][b]) break;
			}
			if (i) --i; // i > 0
			a = S[i][a];
			b = S[i][b];
		}
		cout << a << "\n";
	}

	return 0;
}