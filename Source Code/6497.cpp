#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct UnionFind
{
    vector<int> par;
    UnionFind(int n) : par(n, -1) {}

    int Find(int a)
    {
        if (par[a] < 0)
            return a;
        return par[a] = Find(par[a]);
    }

    bool Union(int a, int b)
    {
        a = Find(a), b = Find(b);
        if (!(a ^ b))
            return false;
        if (Size(a) < Size(b))
            swap(a, b);
        par[a] += par[b];
        par[b] = a;
        return true;
    }

    int Size(int a)
    {
        a = Find(a);
        return -par[a];
    }

    bool IsSame(int a, int b)
    {
        a = Find(a), b = Find(b);
        if (a == b)
            return true;
        else
            return false;
    }
};

struct Edge
{
    int from, to, weight;
    Edge(int from, int to, int weight) : from(from), to(to), weight(weight) {}
};

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);
    int M{}, N{}; // 집의 수, 길의 수

    while (1)
    {
        cin >> M >> N;
        if (!M && !N)
            break; // EOF

        UnionFind uf(M); // 0 ~ M - 1
        vector<Edge> edges(N, Edge(0, 0, 0));
        int costSum{};
        for (Edge &edge : edges)
        {
            cin >> edge.from >> edge.to >> edge.weight;
            costSum += edge.weight;
        }

        sort(begin(edges), end(edges), [](const Edge &e1, const Edge &e2)
             { return e1.weight < e2.weight; });

        int cnt{};
        for (Edge &edge : edges)
        {
            if (uf.IsSame(edge.from, edge.to))
                continue;
            uf.Union(edge.from, edge.to);
            costSum -= edge.weight;
            ++cnt;
            if (cnt == M - 1)
                break; // MST 완성
        }
        cout << costSum << '\n';
    }

    return 0;
}