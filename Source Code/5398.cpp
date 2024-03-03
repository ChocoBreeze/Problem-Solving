// 22240KB, 312ms
#include <iostream>
#include <string>
#include <algorithm>
#include <queue>
#include <vector>

// 필요 없는 구조체 제거
using namespace std;
constinit const int SIZE = 2001;
constinit const int INF = 1 << 30;

int N, M;
vector<bool> used;
vector<vector<int>> adj;
vector<int> A, B, level;

void bfs() {
	queue<int> q;
	for (int n{}; n < N; ++n) {
		if (!used[n]) {
			level[n] = 0;
			q.push(n);
		}
		else level[n] = INF;
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
		vector Map(SIZE, vector<char>(SIZE));
		vector indexMap(SIZE, vector<int>(SIZE));

		int H{}, V{}; cin >> H >> V;
		N = H, M = V;
		used = vector(M, false);
		level = vector(M, 0);
		adj = vector(M, vector<int>());

		for (int h{}; h < H; ++h) { // 가로
			string str;
			int xIn{}, yIn{}; cin >> xIn >> yIn >> str;
			int strLen = static_cast<int>(str.length());
			for (int x{ xIn }, i{}; i < strLen; ++x, ++i) {
				Map[x][yIn] = str[i];
				indexMap[x][yIn] = h;
			}
		}
		for (int v{}; v < V; ++v) { // 세로
			string str;
			int xIn{}, yIn{}; cin >> xIn >> yIn >> str;
			int strLen = static_cast<int>(str.length());
			for (int y{ yIn }, i{}; i < strLen; ++y, ++i) {
				if (Map[xIn][y] == '\0' || Map[xIn][y] == str[i]) continue;
				else { // 다른 문자
					adj[v].push_back(indexMap[xIn][y]);
				}
			}
		}

		int match{};
		A = vector(M, -1);
		B = vector(N, -1);

		while(1) {
			bfs();
			int flow{};
			for (int m{}; m < M; ++m) {
				if (!used[m] && dfs(m)) ++flow;
			}
			if (flow == 0) break;
			match += flow;
		}
		cout << H + V - match << '\n';
	}
	return 0;
}