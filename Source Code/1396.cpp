// Parallel Binary Search
// https://rebro.kr/153
#define FASTIO cin.tie(nullptr)->sync_with_stdio(false)

#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;
constexpr int SIZE = 100010;

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
    int from, to, weight; // weight : 간선의 고유값
    Edge(int from, int to, int weight) : from(from), to(to), weight(weight) {}
    bool operator<(const Edge &other)
    {
        return this->weight < other.weight;
    }
};

struct QueryInfo
{
    int src, dst;
    QueryInfo(int src, int dst) : src(src), dst(dst) {}
    QueryInfo() = default;
};

struct AnswerInfo
{
    int minTemp, Cnt;
    AnswerInfo(int minTemp, int Cnt) : minTemp(minTemp), Cnt(Cnt) {}
    AnswerInfo() = default;
};

int main()
{
    FASTIO;
    int N, M, Q;
    cin >> N >> M;
    vector<Edge> edges;
    edges.reserve(SIZE);
    for (int m{}; m < M; ++m)
    {
        int a, b, c;
        cin >> a >> b >> c;
        edges.push_back(Edge(a, b, c));
    }
    cin >> Q;
    vector<QueryInfo> queries(Q);
    for (QueryInfo &q : queries)
    {
        cin >> q.src >> q.dst;
    }

    sort(begin(edges), end(edges)); // MlogM
    vector<int> l(Q, 1), r(Q, M);
    vector<AnswerInfo> answers(Q);

    while (1)
    {
        vector<vector<int>> mids(M + 1); // 1 ~ m (mids[mid] -> mid 값을 mid로 가지는 index들)
        bool isFinish{true};
        for (int q{}; q < Q; ++q)
        {
            if (l[q] <= r[q])
            { // 답을 아직 못 찾음
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
            { // (mids[mid] -> mid 값을 mid로 가지는 index들)
                int src = queries[idx].src, dst = queries[idx].dst;
                if (uf.Find(src) == uf.Find(dst))
                { // 갈 수 있음.
                    answers[idx].minTemp = now.weight;
                    answers[idx].Cnt = uf.Cnt(src);
                    r[idx] = mid - 1; // 범위 갱신
                }
                else
                    l[idx] = mid + 1; // 해당 개수로는 갈 수 없음
            }
        }
    }

    for (int q{}; q < Q; ++q)
    {
        if (l[q] > M)
            cout << "-1\n"; // 갈 수 없음
        else
            cout << answers[q].minTemp << ' ' << answers[q].Cnt << '\n';
    }

    return 0;
}