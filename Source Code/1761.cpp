#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct edge {
	int to;
	int weight;
	edge(int t, int w) : to(t), weight(w) {}
};

struct parent_dist {
	int parent;
	int dist;
	parent_dist(int p, int d) : parent(p), dist(d) {}
};

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	int N, M;
	cin >> N;
	int a, b, w;
	vector<vector<edge>> Edges(N+1); // 1 ~ N
	for (int i = 0; i < N - 1; ++i) {
		cin >> a >> b >> w;
		Edges[a].push_back(edge(b, w));
		Edges[b].push_back(edge(a, w));
	}
	vector<int> depth(N + 1, 50000);
	vector<vector<parent_dist>> S(17, vector<parent_dist> (N+1, parent_dist(0, 0))); //2^16 = 65536
	queue<int> Q;
	depth[1] = 0;
	Q.push(1);
	while (!Q.empty()) {
		int now = Q.front();
		Q.pop();
		for (auto& i : Edges[now]) {
			if (depth[i.to] == 50000) {
				depth[i.to] = depth[now] + 1;
				Q.push(i.to);
				S[0][i.to].parent = now;
				S[0][i.to].dist = i.weight;
			}
		}
	}
	for (int i = 1; i < 17; ++i) {
		for (int j = 1; j <= N; ++j) {
			S[i][j].parent = S[i - 1][S[i - 1][j].parent].parent;
			S[i][j].dist += S[i - 1][S[i - 1][j].parent].dist; // j의 i-1번째 조상에서 ~ j의 i-1번째 조상의 i-1번째 조상까지의 거리
			S[i][j].dist += S[i - 1][j].dist; // j에서 i-1번째 조상까지 거리 - 빠뜨림!
		}
	}

	cin >> M;
	for (int m = 0; m < M; ++m) {
		cin >> a >> b;
		if (depth[a] < depth[b]) swap(a, b); // a가 더 큼
		int diff = depth[a] - depth[b];
		int answer = 0;
		for (int r = 0; diff > 0; ++r) {
			if (diff & 1) {
				answer += S[r][a].dist;
				a = S[r][a].parent;
			}
			diff >>= 1;
		}
		while (a != b) {
			int i;
			for (i = 0; i < 17; ++i) {
				if (S[i][a].parent == S[i][b].parent) {	
					break;
				}
			}
			if (i) --i;
			answer += S[i][a].dist;
			answer += S[i][b].dist;
			a = S[i][a].parent;
			b = S[i][b].parent;
		}
		cout << answer << "\n";
	}

	return 0;
}