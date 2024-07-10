// HLD
// https://justicehui.github.io/hard-algorithm/2020/01/24/hld/
// https://m.blog.naver.com/kks227/221413353934
// https://blog.naver.com/jinhan814/222146989211

#include <iostream>
#include <vector>
#include <algorithm>
#include <bitset>

// constinit int MAXSIZE = 200001;
constexpr int MAXSIZE = 200001;
// constinit�� �� �ǰ� constexpr�� �ǳ�

int N, M;

using namespace std;

vector<vector<int>> adjMatrix;

struct Edge
{
    int from, to, weight;
    Edge(int from = 0, int to = 0, int weight = 0) : from(from), to(to), weight(weight) {}
};
vector<Edge> edges;

struct MSTUnionFind
{
    // 10�� �� �� �� �߰������� �� ���� �� �ִ� ���� ������ 10�� => MAXIMUM 20��
    vector<int> siz, maxTemp, par;

    MSTUnionFind(int n) : siz(n, 0), maxTemp(n, 0), par(n, 0)
    {
        int halfN = n >> 1;
        for (int i{}; i < n; ++i)
        { // n = N * 2 + 1
            par[i] = i;
            if (1 <= i && i <= halfN)
                siz[i] = 1;
        }
    }

    int Find(int a)
    {
        if (a == par[a])
            return a; // siz �迭�� ���� ����
        return par[a] = Find(par[a]);
    }

    void Union(int a, int b)
    {
        a = Find(a), b = Find(b);
        if (a ^ b)
        {
            // ���� ������ ������ ū index�� �θ� �ǵ���
            if (a > b)
                par[b] = a;
            else
                par[a] = b;
        }
    }

    void Make_MST_Edge()
    {
        int cnt{};
        for (Edge &e : edges)
        {
            int a = Find(e.from);
            int b = Find(e.to);
            if (!(a ^ b))
                continue; // a == b
            ++cnt;
            // N + cnt�� ���ο� ���� �����
            // N + cnt�� a, N + cnt�� b ����
            int newIndex{N + cnt};
            Union(a, newIndex);
            Union(b, newIndex);
            siz[newIndex] = siz[a] + siz[b];
            maxTemp[newIndex] = e.weight;

            // newIndex -> a, newIndex -> b ������ ���� �����
            adjMatrix[newIndex].push_back(a);
            adjMatrix[newIndex].push_back(b);
            if (cnt == N - 1)
                break; // MST ���� �Ϸ�
        }
    }
};

struct HLD
{
    vector<int> siz, dep, par, top, in, out; // �� �������� in out�� �ʿ���� ��
    MSTUnionFind uf;
    HLD(int n, MSTUnionFind &&uf) : siz(n, 0), dep(n, 0), par(n, 0), top(n, 0), in(n, 0), out(n, 0), uf(move(uf)) {}

    void dfs1(int curr)
    {
        siz[curr] = 1;
        for (int &next : adjMatrix[curr])
        {
            dep[next] = dep[curr] + 1;
            par[next] = curr;
            dfs1(next);
            siz[curr] += siz[next];
            if (siz[next] > siz[adjMatrix[curr][0]])
                swap(next, adjMatrix[curr][0]);
        }
    }

    int pv{};
    void dfs2(int curr)
    {
        in[curr] = ++pv;
        for (int &next : adjMatrix[curr])
        {
            top[next] = (next == adjMatrix[curr][0]) ? top[curr] : next;
            dfs2(next);
        }
        out[curr] = pv;
    }

    bitset<MAXSIZE> visited;
    void MakeHLD()
    {
        for (int i{1}; i <= N; ++i)
        { // 1 ~ N
            int now = uf.Find(i);
            if (visited[now])
                continue;
            visited[now] = 1;
            top[now] = now;
            dfs1(now);
            dfs2(now);
        }
    }

    int lca(int a, int b)
    {
        while (top[a] != top[b])
        {
            if (dep[top[a]] < dep[top[b]])
                swap(a, b);
            a = par[top[a]];
        }
        if (dep[a] > dep[b])
            swap(a, b);
        return a;
    }
};

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> N >> M;

    const int SIZE = N * 2 + 1;
    MSTUnionFind uf(SIZE); // 1 ~ N => 1 ~ 2 * N
    adjMatrix.assign(SIZE, {});
    // adjMatrix.assign(SIZE, vector<int>()); // ����

    edges.assign(M, {});

    for (Edge &e : edges)
        cin >> e.from >> e.to >> e.weight;

    sort(begin(edges), end(edges), [](const Edge &e1, const Edge &e2)
         { return e1.weight < e2.weight; });
    uf.Make_MST_Edge();

    HLD hld(SIZE, move(uf)); // �׳� hld �ȿ� �� ����ڴ� �̷� �Ÿ�
    hld.MakeHLD();

    int Q{};
    cin >> Q;

    for (int q{}; q < Q; ++q)
    {
        int a{}, b{};
        cin >> a >> b;
        if (hld.uf.Find(a) != hld.uf.Find(b))
        { // �� ��
            cout << "-1\n";
        }
        else
        {
            int c = hld.lca(a, b);
            cout << hld.uf.maxTemp[c] << ' ' << hld.uf.siz[c] << '\n';
        }
    }

    return 0;
}