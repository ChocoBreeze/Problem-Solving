// Parallel Binary Search
// https://rebro.kr/153
#define FASTIO cin.tie(nullptr)->sync_with_stdio(false)

#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;
constexpr int SIZE = 200010;

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

    void Union(int a, int b)
    {
        a = Find(a), b = Find(b);
        if (a ^ b)
        {
            if (Cnt(a) < Cnt(b))
                swap(a, b);
            par[a] += par[b];
            par[b] = a;
        }
    }

    int Cnt(int a)
    {
        a = Find(a);
        return -par[a];
    }
};

struct Edge
{
    int from, to, weight; // weight : ������ ������
    Edge(int from, int to, int weight) : from(from), to(to), weight(weight) {}
    bool operator<(const Edge &other)
    { // �������� ����
        return this->weight > other.weight;
    }
};

struct QueryInfo
{
    int src, dst;
    QueryInfo(int src, int dst) : src(src), dst(dst) {}
    QueryInfo() = default;
};

int main()
{
    FASTIO;
    int N, M, Q;
    cin >> N >> M >> Q;
    vector<Edge> edges;
    edges.reserve(SIZE);
    for (int m{}; m < M; ++m)
    {
        int a, b, c;
        cin >> a >> b >> c;
        edges.push_back(Edge(a, b, c)); // ���� ���� A, B�� ���� ���� �� �־��� �� ������ ����
    }

    vector<QueryInfo> queries(Q);
    for (QueryInfo &q : queries)
    {
        cin >> q.src >> q.dst;
    }

    sort(begin(edges), end(edges)); // MlogM -> 10'000'000
    vector<int> l(Q, 1), r(Q, M);
    vector<int> answers(Q); // maxSpeed

    while (1)
    {
        vector<vector<int>> mids(M + 1); // 1 ~ m (mids[mid] -> mid ���� mid�� ������ index��)
        bool isFinish{true};
        for (int q{}; q < Q; ++q)
        {
            if (l[q] <= r[q])
            { // ���� ���� �� ã��
                isFinish = false;
                int mid = l[q] + (r[q] - l[q]) / 2;
                mids[mid].push_back(q);
            }
        }
        if (isFinish)
            break;
        UnionFind uf(N + 1);

        for (int mid{1}; mid <= M; ++mid)
        {
            Edge &now = edges[mid - 1];
            uf.Union(now.from, now.to);
            for (int idx : mids[mid])
            { // (mids[mid] -> mid ���� mid�� ������ index��)
                int src = queries[idx].src, dst = queries[idx].dst;
                if (uf.Find(src) == uf.Find(dst))
                { // �� �� ����.
                    answers[idx] = now.weight;
                    r[idx] = mid - 1; // ���� ����
                }
                else
                    l[idx] = mid + 1; // �ش� �����δ� �� �� ����
            }
        }
    }

    for (int answer : answers)
    {
        cout << answer << '\n';
    }

    return 0;
}