// https://justicehui.github.io/hard-algorithm/2020/01/24/hld/
// https://www.acmicpc.net/problem/13510
// https://www.acmicpc.net/source/15341705

// 생 배열 제거

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    int from, to, weight;
    Edge(int from, int to, int weight) : from(from), to(to), weight(weight) {}
};

struct SegTree {
    vector<int> tree;
    int sz; // leaf 시작점

    SegTree(int N) {
        sz = 1;
        while (sz < N) sz <<= 1;
        sz <<= 1; // sz = pow(2, ceil(log2(N)));
        tree.assign(sz, 0);
        sz >>= 1;
    }

    void init() {
        for (int i{ sz - 1 }; i > 0; --i) {
            tree[i] = max(tree[i + i], tree[i + i + 1]);
        }
    }

    void update(int x, int v) {
        x += sz - 1; tree[x] = v;
        while (x >>= 1) {
            // tree[x] = max(tree[x << 1], tree[x << 1 | 1]);
            tree[x] = max(tree[x + x], tree[x + x + 1]);
        }
    }

    int query(int l, int r) {
        l += sz - 1, r += sz - 1;
        int ret{};
        while (l <= r) {
            if (l & 1) ret = max(ret, tree[l++]);
            if (~r & 1) ret = max(ret, tree[r--]);
            l >>= 1, r >>= 1;
        }
        return ret;
    }
};
/*
* sz[i] : i를 루트로 하는 트리의 크기
* depth[i] : i의 깊이 (dfs1)
* par[i] : i의 부모 정점 (dfs1)
* top[i] : i가 속한 체인의 가장 위에 있는 정점 (dfs2)
* in[i] : i의 DFS Ordering(들어갈 때) (dfs2) -> segment Tree의 leaf node index가 된다.
* out[i] : i의 DFS Ordering(나올 때) (dfs2)
*/
vector<int> sz, depth, par, top, in, out;
// int sz[101010], depth[101010], par[101010], top[101010], in[101010], out[101010];
vector<vector<int>> g; // dfs로 나오는 결과
vector<vector<int>> graph; //입력 - 양방향 그래프

vector<int> visited;
void dfs(int v = 0) {
    visited[v] = 1;
    for (auto& i : graph[v]) {
        if (visited[i]) continue;
        g[v].push_back(i);
        dfs(i);
    }
}

void dfs1(int v = 0) {
    sz[v] = 1;
    for (auto& i : g[v]) {
        depth[i] = depth[v] + 1; par[i] = v;
        dfs1(i); sz[v] += sz[i];
        if (sz[i] > sz[g[v][0]]) swap(i, g[v][0]);
    }
}

int pv;
void dfs2(int v = 0) {
    in[v] = ++pv;
    for (auto& i : g[v]) {
        top[i] = (i == g[v][0]) ? top[v] : i;
        dfs2(i);
    }
    out[v] = pv;
}

void update(SegTree& st, Edge& e, int w) {
    if (depth[e.from] > depth[e.to]) st.update(in[e.from], w);
    else st.update(in[e.to], w);
}

int query(SegTree& st, int a, int b) {
    int ret{};
    while (top[a] ^ top[b]) {
        if (depth[top[a]] < depth[top[b]]) swap(a, b);
        int& edgeTop = top[a];
        ret = max(ret, st.query(in[edgeTop], in[a]));
        a = par[edgeTop];
    }
    if (depth[a] > depth[b]) swap(a, b);
    ret = max(ret, st.query(in[a] + 1, in[b])); // in[a]에는 par[a]에서 a까지 가는 간선 정보가..
    return ret;
}

int main() {
    cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
    int N{}, q{}; cin >> N; // 정점 수

    sz.assign(N, 0);
    depth.assign(N, 0);
    par.assign(N, 0);
    top.assign(N, 0);
    in.assign(N, 0);
    out.assign(N, 0);
    visited.assign(N, 0);
    vector<Edge> edges(N - 1, Edge(0,0,0));
    graph = vector<vector<int>>(N);
    g = vector<vector<int>>(N);
    SegTree st(N);

    for (auto& [u, v, w] : edges) {
        cin >> u >> v >> w;
        --u, --v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    // 기본적인 dfs
    dfs(); dfs1(); dfs2();

    // Segment Tree 구성
    for (auto& e : edges) {
        update(st, e, e.weight);
    }
    st.init();

    cin >> q;
    while (q--) {
        //1 v w : update v w
        //2 s e : query s e
        int op, a, b; cin >> op >> a >> b;
        if (op == 1) {
            --a; // index 1개 감소
            update(st, edges[a], b);
        }
        else {
            --a, --b;
            cout << query(st, a, b) << '\n';
        }
    }

    return 0;
}