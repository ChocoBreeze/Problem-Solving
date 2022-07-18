#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct e_t {
	int dst;
	int weight;
	e_t(int d, int w) : dst(d), weight(w) {}
};

struct info {
	int parent;
	int min_w;
	int max_w;
	info(int p, int min_w, int max_w) : parent(p), min_w(min_w), max_w(max_w) {}
};

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	int N, K;
	int A, B, C;
	cin >> N;
	vector<vector<e_t>> AL(N + 1); // 1 ~ N
	for (int i = 1; i < N; ++i) { // tree - 인접 리스트
		cin >> A >> B >> C;
		AL[A].push_back(e_t(B, C));
		AL[B].push_back(e_t(A, C));
	}

	// depth 파악
	// 2 ^ 17 = 131,072 (최대 17번째 부모까지 표현 가능 -> 18)
	vector<vector<info>> Parent(18, vector<info>(N + 1, info(0, 0, 0)));
	vector<int> Depth(N + 1, -1);
	queue<int> Q;
	Q.push(1); // 1을 root로 보기
	Depth[1] = 0;
	while (!Q.empty()) { // bfs로 depth 계산(dfs도 가능)
		int now = Q.front();
		Q.pop();
		for (auto& n : AL[now]) {
			if (Depth[n.dst] == -1) {
				Q.push(n.dst);
				Depth[n.dst] = Depth[now] + 1;
				Parent[0][n.dst].parent = now;
				Parent[0][n.dst].max_w = n.weight;
				Parent[0][n.dst].min_w = n.weight;
			}
		}
	}

	// sparse table 
	for (int r = 1; r < 18; ++r) {
		for (int i = 1; i <= N; ++i) {
			Parent[r][i].parent = Parent[r - 1][Parent[r - 1][i].parent].parent;
			Parent[r][i].max_w = max(Parent[r - 1][Parent[r - 1][i].parent].max_w, Parent[r - 1][i].max_w);
			Parent[r][i].min_w = min(Parent[r - 1][Parent[r - 1][i].parent].min_w, Parent[r - 1][i].min_w);
		}
	}

	// Query
	cin >> K;
	for (int k = 0; k < K; ++k) {
		cin >> A >> B;
		if (Depth[A] > Depth[B]) {
			swap(A, B);
		}
		int answer_min = 1000001, answer_max = -1;
		// 1. Depth 맞추기
		int diff = Depth[B] - Depth[A];
		// diff가 10 = 1010(2) 해당 자리수에 성분 존재하는 경우 jump
		for (int r = 0; diff > 0; ++r) {
			if (diff & 1) {
				answer_min = min(answer_min, Parent[r][B].min_w);
				answer_max = max(answer_max, Parent[r][B].max_w);
				B = Parent[r][B].parent; // 갱신을 나중에
			}
			diff >>= 1;
		}
		// 2. LCA 찾기
		while (A != B) {
			int r;
			for (r = 0; r < 18; ++r) { // 만나는 r을 찾기 -> 최소 공통 조상은 아니므로 더 찾을 필요 있음
				if (Parent[r][A].parent == Parent[r][B].parent) break;
			}
			if (r > 0) --r;
			answer_min = min(answer_min, Parent[r][B].min_w);
			answer_max = max(answer_max, Parent[r][B].max_w);
			answer_min = min(answer_min, Parent[r][A].min_w);
			answer_max = max(answer_max, Parent[r][A].max_w);
			A = Parent[r][A].parent, B = Parent[r][B].parent; // 갱신을 나중에
		}
		cout << answer_min << " " << answer_max << "\n";
	}
	return 0;
}