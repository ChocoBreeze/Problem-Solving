// MST(Minimum Spanning Tree) + PBS(Parallel Binary Search)
// https://justicehui.github.io/ps/2020/08/31/BOJ16074/
// 왜 MST가 필요한가,, (거리가 누적되는 것이 아닌 도달하기 까지 최대 간선만 알면 된다)
// 간선 구성을 어떻게 해야 하는가? 두 정점을 어차피 다 밟아야 하니 => 두 정점을 연결하는 간선의 경우 두 정점의 높이 값 중 최대값이 weight가 된다.
// 이후에는 MST 구성해가면서 두 정점이 연결되어 있는지 확인 - PBS
// 18756KB, 256ms

#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;
using pii = pair<int, int>;
int m{}, n{};

struct Edge {
	int from, to, weight;
	Edge(int from, int to, int weight) : from{ from }, to{ to }, weight{ weight } {}
	bool operator<(const Edge& other) const {
		return weight < other.weight;
	}
};
inline int CoordToNum(int i, int j) {
	return i * n + j;
}

struct UnionFind {
	vector<int> par;
	UnionFind(int N) : par(N, -1) {}

	int Find(int a) {
		if (par[a] < 0) return a;
		return par[a] = Find(par[a]);
	}

	bool Union(int a, int b) {
		a = Find(a), b = Find(b);
		if (a == b) return false;
		if (par[a] > par[b]) swap(a, b);
		par[a] += par[b];
		par[b] = a;
		return true;
	}
};

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int q{}; cin >> m >> n >> q;
	const int SIZE = m * n;

	vector cost(m, vector<int>(n, 0));
	for (auto& row : cost) {
		for (auto& c : row) {
			cin >> c;
		}
	}

	vector<Edge> edges;
	for (int i{}; i < m; ++i) {
		for (int j{}; j < n; ++j) {
			if (i + 1 < m) edges.emplace_back(CoordToNum(i, j), CoordToNum(i + 1, j), max(cost[i][j], cost[i + 1][j]));
			if (j + 1 < n) edges.emplace_back(CoordToNum(i, j), CoordToNum(i, j + 1), max(cost[i][j], cost[i][j + 1]));
		}
	}
	sort(begin(edges), end(edges));

	vector<pii> queries(q, make_pair(0, 0));
	for (auto& [from, to] : queries) {
		int x1{}, y1{}, x2{}, y2{}; cin >> x1 >> y1 >> x2 >> y2; --x1, --y1, --x2, --y2;
		from = CoordToNum(x1, y1);
		to = CoordToNum(x2, y2);
	}

	const int HI = static_cast<int>(edges.size());
	vector<int> lo(q, 0), hi(q, HI);
	while (1) {
		bool notFinish{};
		vector mids(HI + 1, vector<int>());
		for (int i{}; i < q; ++i) {
			if (lo[i] < hi[i]) {
				int mid = lo[i] + ((hi[i] - lo[i]) >> 1);
				mids[mid].push_back(i); // index
				notFinish = true;
			}
		}
		if (!notFinish) break;

		
		UnionFind uf(SIZE);
		for (int i{}; i < HI; ++i) { // 합치는 edge들
			auto& [from, to, weight] = edges[i];
			uf.Union(from, to);
			for (int& idx : mids[i]) { // 중간값이 i인 query의 idx들
				auto& [v1, v2] = queries[idx];
				if (uf.Find(v1) == uf.Find(v2)) hi[idx] = i;
				else lo[idx] = i + 1;
			}
		}
	}
	for (int i{}; i < q; ++i) {
		auto& [from, to] = queries[i];
		if (from == to) cout << cost[from / n][from % n] << '\n'; // 이미 갈 수 있는 경우
		// else if (lo[i] > HI) cout << edges.back().weight << '\n';
		// else cout << edges[lo[i]].weight << '\n';
		else cout << edges[hi[i]].weight << '\n';
	}

	return 0;
}