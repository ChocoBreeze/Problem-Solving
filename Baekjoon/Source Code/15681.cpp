#include <iostream>
#include <vector>
#include <stack>
#include <bitset>

using namespace std;
vector<vector<int>> graph;
vector<int> Size;
bitset<100010> visited;

int dfs(int curr)
{
    int cnt{1};
    for (int &next : graph[curr])
    {
        if (visited[next])
            continue;
        visited[next] = 1;
        cnt += dfs(next);
    }
    Size[curr] = cnt;
    return cnt;
}

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);
    int N, R, Q; // 정점, 루트, 쿼리 수
    cin >> N >> R >> Q;

    graph = vector<vector<int>>(N + 1);
    Size = vector<int>(N + 1, 0);
    for (int n{1}; n < N; ++n)
    {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    visited[R] = 1;
    dfs(R);

    for (int q{}; q < Q; ++q)
    {
        int in;
        cin >> in;
        cout << Size[in] << '\n';
    }

    return 0;
}