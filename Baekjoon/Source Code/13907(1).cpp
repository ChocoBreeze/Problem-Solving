// https://www.acmicpc.net/source/59722295
// �ð� ���̱� - 7092kb, 20ms
// ������ ������ �� �ִ� ��θ� ���� -> �ش� ��κ��� �� ���� ��θ� ������ �ϴ� ��� ���� �ּ� ����ᰡ �ƴ�.

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
constexpr int INF = static_cast<int>(21e8);

// Data ���� (from ���� + �񱳽� ����)
struct Data
{
    int cost; // ���� ���
    int cnt;  // ������ ���� ����
    int to;   // ���� ����
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
{ // ���� : <�ִ� �Ÿ�, ��� ��>
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
    DP[S][0] = 0; // [����][������ ��� ��] �� �ɸ� �ִ� �Ÿ�

    // �߰�
    vector<Info> minDist(N + 1, Info(INF, INF)); // ����: <�ִ� �Ÿ�, ��� ��>
    minDist[S] = {0, 0};
    // ó������ ���� �ִ� �Ÿ����� �� �� ��� ���� �ʿ��� ����� ��� �ּ� ����ᰡ ���� �� ����.
    // ���� �� ��� ���� �ٿ��� �� ����!

    // �� ����
    while (!pq.empty())
    {
        Data now = pq.top();
        pq.pop();

        if (minDist[now.to].minDist < now.cost && minDist[now.to].cnt <= now.cnt)
            continue; // �� �ʿ� ����

        for (Edge &next : graph[now.to])
        { // ������ ��
            int nextDist = now.cost + next.weight;
            if (nextDist < minDist[next.to].minDist)
            { // minDist�� ������ ������ ���
                minDist[next.to] = {nextDist, now.cnt + 1};
                DP[next.to][now.cnt + 1] = nextDist;
                pq.push(Data(nextDist, now.cnt + 1, next.to));
            }
            // �̹� ���� �ִ� ��� �������� �� �� ��μ��� �ʿ��� ��쿡 ���� Ȯ���� �ʿ� ����!!
            else if (now.cnt + 1 < minDist[next.to].cnt && nextDist < DP[next.to][now.cnt + 1])
            {
                DP[next.to][now.cnt + 1] = now.cost + next.weight;
                pq.push(Data(now.cost + next.weight, now.cnt + 1, next.to));
            }
        }
    }

    vector<pair<int, int>> res; // <�ִ� �Ÿ�, ��� ��> : ���� ��忡 ������ �ִ� �Ÿ��� ��� ���� �����ϴ� �迭
    for (int i{1}; i <= minDist[D].cnt; ++i)
    {
        if (DP[D][i] != INF)
            res.push_back(make_pair(DP[D][i], i));
    }

    // vector<int> taxes(K + 1, 0); -- ����
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