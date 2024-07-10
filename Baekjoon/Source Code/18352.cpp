#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
const int INF = 1000000000;
int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	int N, M, K, X, a, b;
	cin >> N >> M >> K >> X;
	vector<vector<int>> AL(N + 1);
	for (int m = 0; m < M;++m) {
		cin >> a >> b;
		AL[a].push_back(b);
	}
	vector<int> dist(N + 1, INF);
	queue<int> Q;
	dist[X] = 0;
	Q.push(X);
	int chk = false;
	while (!Q.empty()) {
		int now = Q.front();
		Q.pop();
		for (auto& e : AL[now]) {
			if (dist[e] == INF) {
				dist[e] = dist[now] + 1;
				Q.push(e);
				if (dist[e] == K) chk = true;
			}
		}
	}
	if (chk) {
		for (int i = 1; i <= N; ++i) {
			if (dist[i] == K) cout << i << "\n";
		}
	}
	else {
		cout << -1;
	}
	return 0;
}