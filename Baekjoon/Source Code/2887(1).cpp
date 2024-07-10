// 8288KB, 84ms
// Kruskal
// 코드 변경
#include <iostream>
#include <queue> // priority_queue
#include <vector> // vector
#include <algorithm> // swap, sort, min
#include <cmath> // abs

using namespace std;

struct UnionFind {
	vector<int> par;
	UnionFind(int n) : par(n, -1) {}

	int root(int x) {
		if (par[x] < 0) return x;
		return par[x] = root(par[x]);
	}
	
	bool is_same(int x, int y) {
		x = root(x), y = root(y);
		return x == y;
	}

	bool unite(int x, int y) {
		x = root(x), y = root(y);
		if (x == y) return false;
        if(size(x) < size(y)) swap(x, y);
        par[x] += par[y];
		par[y] = x;
		return true;
	}
    int size(int x) {
        x = root(x);
        return -par[x];
    }
};

struct Coord {
	int original_index;
	int pos;
	Coord(int index, int pos) : original_index(index), pos(pos) {}
    bool operator<(const Coord& other) const {
        return this->pos < other.pos;
    }
};

struct Edge {
	int src;
	int dst;
	int weight;
	Edge(int src, int dst, int weight) : src(src), dst(dst), weight(weight) {}
};

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	int N; cin >> N;
	vector<Coord> xPos(N, Coord(0, 0));
    vector<Coord> yPos(N, Coord(0, 0));
    vector<Coord> zPos(N, Coord(0, 0));
	for (int i{}; i < N; ++i) {
		zPos[i].original_index = yPos[i].original_index = xPos[i].original_index = i;
		cin >> xPos[i].pos >> yPos[i].pos >> zPos[i].pos;
	}
    
    // 모든 정점을 다 돌면서 간선 만들 수 없음.
    // 각 좌표만 비교해서 가깝다 생각하는 간선 만들기
    sort(begin(xPos), end(xPos));
    sort(begin(yPos), end(yPos));
    sort(begin(zPos), end(zPos));

    vector<Edge> edges; // 두 행성을 연결하는 비용 = min(|Xa - Xb|, |Ya - Yb|, |Za - Zb|)
    // 각 좌표에 대해 정렬 후 간선 만들어도 됨.
    edges.reserve(3 * N);
    for (int i{}; i < N - 1; ++i) {
		edges.emplace_back(xPos[i].original_index, xPos[i + 1].original_index, abs(xPos[i].pos - xPos[i+1].pos));
        edges.emplace_back(yPos[i].original_index, yPos[i + 1].original_index, abs(yPos[i].pos - yPos[i+1].pos));
        edges.emplace_back(zPos[i].original_index, zPos[i + 1].original_index, abs(zPos[i].pos - zPos[i+1].pos));
	}

    auto compare = [](const Edge& e1, const Edge& e2) {
        return e1.weight < e2.weight;
    };
    sort(begin(edges), end(edges), compare);

	UnionFind uf(N); // 0 ~ N
    // 굳이 PQ 쓸 필요 없음.

	int ans{}, selectedEdgeCnt{}, edgeNum{static_cast<int>(edges.size())};
    for(int i{};i<edgeNum && selectedEdgeCnt != N - 1;++i) {
        auto& [from, to, weight] = edges[i];
        if(uf.is_same(from, to)) continue;
        ans += weight;
        uf.unite(from, to);
        selectedEdgeCnt++;
    }
	cout << ans;
	return 0;
}