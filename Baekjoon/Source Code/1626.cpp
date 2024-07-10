// https://www.acmicpc.net/problem/15481
// 55292KB, 192ms
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <tuple>

using namespace std;
using ll = long long;
using pii = pair<int, int>;
constinit const int SIZE = 16; // 1 << 16 = 65536
constinit const ll INF = 1LL << 31;

struct UnionFind {
	vector<int> par;
	UnionFind(int n) : par(n, -1) {}
	int Find(int a) {
		if (par[a] < 0) return a;
		return par[a] = Find(par[a]);
	}
	void Union(int a, int b) {
		a = Find(a), b = Find(b);
		if (a == b) return;
		par[a] += par[b];
		par[b] = a;
	}
};

struct Edge {
	int u, v, w;
	Edge(int u, int v, int w) : u(u), v(v), w(w) {}
	bool operator<(const Edge& other) {
		return w < other.w;
	}
};

struct GraphEdge {
	int to, weight;
	GraphEdge(int to, int weight) : to(to), weight(weight) {}
};

void UpdateWeight(int& firstWeight, int& secondWeight, int& w1, int &w2) {
	if (firstWeight < w1) {
		secondWeight = max({ secondWeight, firstWeight, w2 });
		firstWeight = w1;
	}
	else if (firstWeight > w1) {
		secondWeight = max(secondWeight, w1);
	}
	else { // firstWeight == w1
		secondWeight = max(secondWeight, w2);
	}
}

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);

	int N{}, M{}; cin >> N >> M;
	vector<Edge> edgs(M, Edge(0, 0, 0));
	for (int m{}; m < M; ++m) {
		auto& [u, v, w] = edgs[m];
		cin >> u >> v >> w;
	}

	sort(begin(edgs), end(edgs)); // 가중치 오름차순

	// 1. MST 구하기 + 사용한 간선으로 adjacency list 생성
	vector<vector<GraphEdge>> graph(N + 1);
	UnionFind uf(N + 1); int eCnt{}; ll wSum{};
	for (auto& [u, v, w] : edgs) {
		if (uf.Find(u) == uf.Find(v)) continue;
		uf.Union(u, v); 
		++eCnt; 
		wSum += w;
		graph[u].emplace_back(v, w);
		graph[v].emplace_back(u, w);
		if (eCnt == N - 1) break;
	}
	if (eCnt != N - 1) { // MST 존재하지 않음.
		cout << "-1\n";
		return 0;
	}

	// 2. Sparse Table 만들기 - LCA
	vector sparseT(SIZE, vector<int>(N + 1, 0)); // par
	vector sparseTWeight(SIZE, vector(N + 1, vector<int>(2, -1))); // 가장 큰 weight 2개
	queue<int> q; vector<int> depth(N + 1, 0);
	q.push(1); depth[1] = 1;
	while (!q.empty()) {
		int now = q.front(); q.pop();
		for (auto& [to, weight] : graph[now]) {
			if (depth[to]) continue;
			depth[to] = depth[now] + 1;
			q.push(to);
			sparseT[0][to] = now; // par
			sparseTWeight[0][to][0] = weight;
 		}
	}

	for (int s{1}; s < SIZE; ++s) {
		for (int v{ 1 }; v <= N; ++v) {
			sparseT[s][v] = sparseT[s - 1][sparseT[s - 1][v]];
			// 4개 중 최대 2개
			sparseTWeight[s][v][0] = sparseTWeight[s - 1][v][0];
			sparseTWeight[s][v][1] = sparseTWeight[s - 1][v][1];
			UpdateWeight(sparseTWeight[s][v][0], sparseTWeight[s][v][1], sparseTWeight[s - 1][sparseT[s - 1][v]][0], sparseTWeight[s - 1][sparseT[s - 1][v]][1]);
		}
	}

	ll answer{INF};
	for (auto& [u, v, w] : edgs) {
		int uTemp{ u }, vTemp{ v };
		if (depth[uTemp] > depth[vTemp]) swap(uTemp, vTemp);

		int firstWeight{-1}, secondWeight{-1}; // weight가 0인 간선 주의
		int diff = depth[vTemp] - depth[uTemp];
		for (int d{}; diff > 0; ++d, diff >>= 1) {
			if (diff & 1) {
				UpdateWeight(firstWeight, secondWeight, sparseTWeight[d][vTemp][0], sparseTWeight[d][vTemp][1]);
				vTemp = sparseT[d][vTemp];
			}
		}

		while (uTemp != vTemp) {
			int d{};
			for (;d < SIZE; ++d) {
				if (sparseT[d][uTemp] == sparseT[d][vTemp]) break;
			}
			if (d) --d;
			UpdateWeight(firstWeight, secondWeight, sparseTWeight[d][vTemp][0], sparseTWeight[d][vTemp][1]);
			vTemp = sparseT[d][vTemp];
			UpdateWeight(firstWeight, secondWeight, sparseTWeight[d][uTemp][0], sparseTWeight[d][uTemp][1]);
			uTemp = sparseT[d][uTemp];
		}
		if (firstWeight != -1 && wSum < wSum - firstWeight + w) answer = min(answer, wSum - firstWeight + w);
		if (secondWeight != -1 && wSum < wSum - secondWeight + w) answer = min(answer, wSum - secondWeight + w);
	}
	if (answer == INF) answer = -1; // 두 번째로 작은 스패닝 트리 존재하지 않음.
	cout << answer << '\n';
	return 0;
}