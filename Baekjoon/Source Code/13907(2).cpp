// https://www.acmicpc.net/source/37029568
// 더 빠른 코드 발견!!
// 그냥 큐로도 가능 ㄷㄷ
// 2968KB, 12ms

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>

using namespace std;
constexpr int INF = static_cast<int>(21e8);
constexpr int SIZE = 1001;

struct Data
{
    int pos, cnt, cost;
    Data(int pos, int cnt, int cost) : pos(pos), cnt(cnt), cost(cost) {}
};

struct Edge
{
    int to;
    int weight;
    Edge(int to, int weight) : to(to), weight(weight) {}
};

using Graph = vector<vector<Edge>>;
int dist[SIZE];

int main()
{
    cin.tie(NULL)->sync_with_stdio(false);
    int N, M, K;
    cin >> N >> M >> K;
    Graph graph(N + 1);

    int S, D; // Start, Destination
    cin >> S >> D;
    for (int m{}; m < M; ++m)
    {
        int a, b, w;
        cin >> a >> b >> w;
        // bidirectional
        graph[a].push_back(Edge(b, w));
        graph[b].push_back(Edge(a, w));
    }

    memset(dist, 0x3f, sizeof(dist)); // 1061109567 (헐)

    vector<pair<int, int>> res;
    queue<Data> q;
    q.push(Data(S, 0, 0));
    dist[S] = 0;

    while (!q.empty())
    {
        Data top = q.front();
        q.pop();
        if (top.pos == D)
        {
            res.emplace_back(top.cost, top.cnt); // 만들어줘서 넣어주기 때문에 emplace_back 가능
            // res.push_back(top.cost, top.cnt); -> X
            continue;
        }
        for (Edge &w : graph[top.pos])
        {
            if (dist[w.to] <= top.cost + w.weight)
                continue;
            dist[w.to] = top.cost + w.weight;
            q.push({w.to, top.cnt + 1, top.cost + w.weight});
        }
    }

    int tax{};
    for (int k{0}; k <= K; ++k)
    {
        int ans{INF}, in{};
        if (k)
            cin >> in;
        tax += in;
        for (auto &r : res)
        {
            ans = min(ans, r.first + tax * r.second);
        }
        cout << ans << '\n';
    }

    return 0;
}