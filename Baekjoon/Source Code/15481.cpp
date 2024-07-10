// 1. MST 만들기
// 2. Sparse Table 만들기 - LCA
// - 부모 정점 + 가장 큰 가중치 갱신
// 기존 MST에 포함된 간선의 경우 => 기존 MST가 답
// 아닌 경우 lca 찾아서 가장 큰 가중치 빼고 새 가중치로 갱신.
// 50084KB, 228ms
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;
using ll = long long;
using pii = pair<int, int>;
constinit const int SIZE = 19; // 1 << 19 = 524288

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
	int u, v, w, index, used;
	Edge(int u, int v, int w, int index, int used) : u(u), v(v), w(w), index(index), used(used) {}
	bool operator<(const Edge& other) {
		return w < other.w;
	}
};

struct GraphEdge {
	int to, weight;
	GraphEdge(int to, int weight) : to(to), weight(weight) {}
};
using Data = GraphEdge;
// {to, weight} => {par, weight}

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);

	int N{}, M{}; cin >> N >> M;
	vector<Edge> edgs(M, Edge(0, 0, 0, 0, 0));
	for (int m{}; m < M; ++m) {
		auto& [u, v, w, index, used] = edgs[m];
		cin >> u >> v >> w;
		index = m;
	}

	sort(begin(edgs), end(edgs)); // 가중치 오름차순

	// 1. MST 구하기 + 사용한 간선 저장
	vector<vector<GraphEdge>> graph(N + 1);
	UnionFind uf(N + 1); int eCnt{}; ll wSum{};
	for (auto& [u, v, w, index, used] : edgs) {
		if (uf.Find(u) == uf.Find(v)) continue;
		uf.Union(u, v); 
		++eCnt; 
		wSum += w, used = 1;
		graph[u].emplace_back(v, w);
		graph[v].emplace_back(u, w);
		if (eCnt == N - 1) break;
	}
	// cout << wSum << '\n';

	// 2. Sparse Table 만들기 - LCA
	vector sparseT(SIZE, vector<Data>(N + 1, Data(0, 0)));
	queue<int> q; vector<int> depth(N + 1, 0);
	q.push(1); depth[1] = 1;
	while (!q.empty()) {
		int now = q.front(); q.pop();
		for (auto& [to, weight] : graph[now]) {
			if (depth[to]) continue;
			depth[to] = depth[now] + 1;
			q.push(to);
			sparseT[0][to].to = now; // par
			sparseT[0][to].weight = weight;
 		}
	}

	for (int s{1}; s < SIZE; ++s) {
		for (int v{ 1 }; v <= N; ++v) {
			sparseT[s][v].to = sparseT[s - 1][sparseT[s - 1][v].to].to;
			sparseT[s][v].weight = max(sparseT[s - 1][v].weight, sparseT[s - 1][sparseT[s - 1][v].to].weight);
		}
	}

	sort(begin(edgs), end(edgs), [](const Edge& e1, const Edge& e2) {
		return e1.index < e2.index;
		});

	for (auto& [u, v, w, index, used] : edgs) {
		if (used) {
			cout << wSum << '\n';
			continue;
		}

		int uTemp{ u }, vTemp{ v };
		if (depth[uTemp] > depth[vTemp]) swap(uTemp, vTemp);

		int maxWeight{}; // -1 -> 0
		int diff = depth[vTemp] - depth[uTemp];
		for (int d{}; diff > 0; ++d, diff >>= 1) {
			if (diff & 1) {
				maxWeight = max(maxWeight, sparseT[d][vTemp].weight);
				vTemp = sparseT[d][vTemp].to;
			}
		}

		while (uTemp != vTemp) {
			int d{};
			for (;d < SIZE; ++d) {
				if (sparseT[d][uTemp].to == sparseT[d][vTemp].to) break; // 악 이거 왜 등호 1개 적었어 ㄴ허알ㄴ어링니런이렁ㄴ
			}
			if (d) --d;
			maxWeight = max(maxWeight, sparseT[d][vTemp].weight);
			vTemp = sparseT[d][vTemp].to;
			maxWeight = max(maxWeight, sparseT[d][uTemp].weight);
			uTemp = sparseT[d][uTemp].to;
		}
		cout << wSum - maxWeight + w << '\n';
	}

	return 0;
}