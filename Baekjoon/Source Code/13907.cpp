// 7152kb, 528ms
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
constexpr int INF = static_cast<int>(21e8);

struct Data
{
    int from; // 어디에서 왔는지
    int cost; // 누적 비용
    int cnt;  // 지나온 도시 개수
    int to;   // 현재 도시
    Data(int from, int cost, int cnt, int to) : from(from), cost(cost), cnt(cnt), to(to) {}
    bool operator<(const Data &other) const
    { // PQ(min heap)
        return this->cnt > other.cnt;
    }
};

struct Edge
{
    int to;
    int weight;
    Edge(int to, int weight) : to(to), weight(weight) {}
};

using Graph = vector<vector<Edge>>;

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

    vector<int> taxes(K + 1, 0);
    for (int k{1}; k <= K; ++k)
    {
        cin >> taxes[k];
    }

    priority_queue<Data> pq;
    pq.push(Data(-1, 0, 0, S));

    vector<vector<int>> DP(N + 1, vector<int>(N + 1, INF));
    DP[S][0] = 0;

    while (!pq.empty())
    {
        Data now = pq.top();
        pq.pop();

        if (DP[now.to][now.cnt] != now.cost)
            continue; // 최소값이 아님
        if (now.cnt == N - 1)
            continue;

        for (Edge &next : graph[now.to])
        { // 인접한 곳
            if (next.to == now.from)
                continue; // 다시 돌아가는 거 방지
            if (DP[next.to][now.cnt + 1] > now.cost + next.weight)
            {
                DP[next.to][now.cnt + 1] = now.cost + next.weight;
                pq.push(Data(now.to, now.cost + next.weight, now.cnt + 1, next.to));
            }
        }
    }

    for (int k{0}; k <= K; ++k)
    { // NK
        int ans{INF};
        for (int n{}; n < N; ++n)
        {
            DP[D][n] += n * taxes[k];
            ans = min(ans, DP[D][n]); // int 안 넘을 듯?
        }
        cout << ans << '\n';
    }

    return 0;
}