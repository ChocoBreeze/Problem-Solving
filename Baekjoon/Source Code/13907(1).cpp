// https://www.acmicpc.net/source/59722295
// 시간 줄이기 - 7092kb, 20ms
// 세금이 오르기 전 최단 경로를 구함 -> 해당 경로보다 더 많은 경로를 지나야 하는 경우 절대 최소 통행료가 아님.

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
constexpr int INF = static_cast<int>(21e8);

// Data 수정 (from 제거 + 비교식 수정)
struct Data
{
    int cost; // 누적 비용
    int cnt;  // 지나온 도시 개수
    int to;   // 현재 도시
    Data(int cost, int cnt, int to) : cost(cost), cnt(cnt), to(to) {}
    bool operator<(const Data &other) const
    { // PQ(min heap)
        if (this->cost == other.cost)
            return this->cnt > other.cnt;
        else
            return this->cost > other.cost;
    }
};

struct Info
{ // 정점 : <최단 거리, 경로 수>
    int minDist;
    int cnt;
    Info(int minDist, int cnt) : minDist(minDist), cnt(cnt) {}
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

    priority_queue<Data> pq;
    pq.push(Data(0, 0, S));

    vector<vector<int>> DP(N + 1, vector<int>(N + 1, INF));
    DP[S][0] = 0; // [정점][지나온 경로 수] 에 걸린 최단 거리

    // 추가
    vector<Info> minDist(N + 1, Info(INF, INF)); // 정점: <최단 거리, 경로 수>
    minDist[S] = {0, 0};
    // 처음으로 구한 최단 거리보다 더 긴 경로 수가 필요한 경로의 경우 최소 통행료가 나올 수 없음.
    // 봐야 할 경로 수를 줄여줄 수 있음!

    // 식 변경
    while (!pq.empty())
    {
        Data now = pq.top();
        pq.pop();

        if (minDist[now.to].minDist < now.cost && minDist[now.to].cnt <= now.cnt)
            continue; // 볼 필요 없음

        for (Edge &next : graph[now.to])
        { // 인접한 곳
            int nextDist = now.cost + next.weight;
            if (nextDist < minDist[next.to].minDist)
            { // minDist도 갱신이 가능한 경우
                minDist[next.to] = {nextDist, now.cnt + 1};
                DP[next.to][now.cnt + 1] = nextDist;
                pq.push(Data(nextDist, now.cnt + 1, next.to));
            }
            // 이미 구한 최단 경로 개수보다 더 긴 경로수가 필요한 경우에 대해 확인할 필요 없음!!
            else if (now.cnt + 1 < minDist[next.to].cnt && nextDist < DP[next.to][now.cnt + 1])
            {
                DP[next.to][now.cnt + 1] = now.cost + next.weight;
                pq.push(Data(now.cost + next.weight, now.cnt + 1, next.to));
            }
        }
    }

    vector<pair<int, int>> res; // <최단 거리, 경로 수> : 최종 노드에 도착한 최단 거리와 경로 수를 저장하는 배열
    for (int i{1}; i <= minDist[D].cnt; ++i)
    {
        if (DP[D][i] != INF)
            res.push_back(make_pair(DP[D][i], i));
    }

    // vector<int> taxes(K + 1, 0); -- 제거
    int tax{};
    for (int k{0}; k <= K; ++k)
    { // NK
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