// 최종
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
	vector<vector<int>> Al(N + 1);
	for (int i = 1; i < N; ++i) { // 인접 리스트 생성(tree의 간선 = N - 1)
		cin >> a >> b;
		Al[a].push_back(b);
		Al[b].push_back(a);
	}

	// 2^17 = 131072 -> 17번째까지 저장 필요
	//[k][v] 현재 정점(v)에서 2의 K제곱번째 부모의 정점 번호를 저장
	vector<vector<int>> Parent(18, vector<int>(N + 1, 0));
	vector<int> Depth(N + 1, -1);
	queue<int> Q;
	Q.push(1);
	Depth[1] = 0;
	while (!Q.empty()) { // bfs로 depth 계산(dfs도 가능)
		int now = Q.front();
		Q.pop();
		for (int n : Al[now]) {
			if (Depth[n] == -1) {
				Q.push(n);
				Depth[n] = Depth[now] + 1;
				Parent[0][n] = now;
			}
		}
	}
	
	// sparse table
	for (int r = 1; r < 18; ++r) {
		for (int i = 1; i <= N; ++i) {
			// i의 2^r번째 부모 = i의 2^(r-1)번째 부모의 2^(r-1)번째 부모
			Parent[r][i] = Parent[r - 1][Parent[r - 1][i]];
		}
	}

	// Query
	cin >> M;
	for (int m = 0; m < M; ++m) {
		cin >> a >> b;
		if (Depth[a] > Depth[b]) {
			swap(a, b);
		}
		// 1. Depth 맞추기
		int diff = Depth[b] - Depth[a];
		// diff가 10 = 1010(2) 해당 자리수에 성분 존재하는 경우 jump
		for (int r = 0; diff > 0; ++r) {
			if (diff & 1) {
				b = Parent[r][b];
			}
			diff >>= 1;
		}
		// 2. LCA 찾기
		while (a != b) {
			int r;
			for (r = 0; r < 18; ++r) { // 만나는 r을 찾기 -> 최소 공통 조상은 아니므로 더 찾을 필요 있음
				if (Parent[r][a] == Parent[r][b]) break;
			}
			if (r > 0) --r;
			a = Parent[r][a], b = Parent[r][b];
		}
		cout << a << "\n";
	}
	return 0;
}