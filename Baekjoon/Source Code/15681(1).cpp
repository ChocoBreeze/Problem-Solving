// 비재귀 풀이
#include <iostream>
#include <vector>
#include <stack>
#include <bitset>

using namespace std;
vector<vector<int>> graph;
vector<int> Size;
bitset<100010> visited;

struct SData
{
    int from, now, index;
    // 어디에서 왔는지
    // 현재 어디인지
    // 어디부터 봐야 하는지
    SData(int from, int now, int index) : from(from), now(now), index(index) {}
};

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);
    int N, R, Q; // 정점, 루트, 쿼리 수
    cin >> N >> R >> Q;

    graph = vector<vector<int>>(N + 1);
    Size = vector<int>(N + 1, 1);
    for (int n{1}; n < N; ++n)
    {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    stack<SData> S;
    S.push(SData(-1, R, 0));
    visited[R] = 1;

    while (!S.empty())
    {
        SData now = S.top();
        S.pop();

        bool chk{false};
        for (int i{now.index}; i < static_cast<int>(graph[now.now].size()); ++i)
        {

            int next = graph[now.now][i];
            if (visited[next])
                continue;
            chk = true;
            visited[next] = 1;
            S.push(SData(now.from, now.now, i + 1));
            S.push(SData(now.now, next, 0));
            break;
        }
        if (!chk)
        {
            if (now.from != -1)
                Size[now.from] += Size[now.now];
        }
    }

    for (int q{}; q < Q; ++q)
    {
        int in;
        cin >> in;
        cout << Size[in] << '\n';
    }

    return 0;
}