// LCA - sparse table
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	int N, M, a, b;
	cin >> N;
	vector<vector<int>> Edges(N + 1);
	for (int i = 1; i < N; ++i) {
		cin >> a >> b;
		Edges[a].push_back(b);
		Edges[b].push_back(a);
	}
	vector<int> depth(N + 1, 100000);
	// 2^16 = 65536
	vector<vector<int>> S(17, vector<int>(N + 1, 0));
	depth[1] = 0;
	queue<int> Q;
	Q.push(1);
	while (!Q.empty()) {
		int now = Q.front();
		Q.pop();
		for (auto& i : Edges[now]) {
			if (depth[i] < depth[now] + 1) continue;
			depth[i] = depth[now] + 1;
			Q.push(i);
			S[0][i] = now;
		}
	}
	for (int i = 1; i < 17; ++i) {
		for (int j = 1; j <= N; ++j) {
			S[i][j] = S[i - 1][S[i - 1][j]];
		}
	}
	cin >> M;
	for (int m = 0; m < M; ++m) {
		cin >> a >> b;
		if (depth[a] > depth[b]) swap(a, b);
		int diff = depth[b] - depth[a];
		for (int r = 0; diff > 0; ++r) {
			if (diff & 1) b = S[r][b];
			diff >>= 1;
		}
		while (a != b) {
			int i;
			for (i = 0; i < 17; ++i) {
				if (S[i][a] == S[i][b]) break;
			}
			if (i) --i;
			a = S[i][a];
			b = S[i][b];
		}
		cout << a << "\n";
	}
	return 0;
}