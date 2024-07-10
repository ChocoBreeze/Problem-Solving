// https://blog.naver.com/jinhan814/222671607972
// UnionFind! - 144ms
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <tuple>
#include <algorithm>

#define FASTIO cin.tie(nullptr)->sync_with_stdio(false);
using namespace std;
using tii = tuple<int, int, int>;

constexpr int INF = static_cast<int>(21e8);

struct UnionFind
{
    vector<int> par;
    UnionFind(int n) : par(n, -1) {}

    int Find(int x)
    {
        if (par[x] < 0)
            return x;
        return par[x] = Find(par[x]);
    }

    bool Union(int a, int b)
    {
        a = Find(a), b = Find(b);
        if (a ^ b)
        { // a!=b
            if (par[a] > par[b])
                swap(a, b);   // a°¡ bº¸´Ù ÀÛÀ¸¸é
            par[a] += par[b]; // a ¹Ø¿¡ b
            par[b] = a;
            return true;
        }
        return false;
    }
    int Size(int x)
    {
        return -par[Find(x)];
    }
};

int main()
{
    FASTIO;
    int N;
    cin >> N;
    vector<string> Map(N);
    UnionFind UF(N * N);
    for (string &s : Map)
        cin >> s;
    for (int i{}; i < N; ++i)
    {
        for (int j{}; j < N; ++j)
        {
            for (int d{}; d < 4; ++d)
            {
                // »óÇÏÁÂ¿ì
                int nx = i + "1012"[d] - '1';
                int ny = j + "2101"[d] - '1';
                if (nx < 0 || nx >= N || ny < 0 || ny >= N)
                    continue;
                if (Map[i][j] == Map[nx][ny])
                    UF.Union(i * N + j, nx * N + ny);
            }
        }
    }

    priority_queue<tii, vector<tii>, greater<tii>> PQ; // min heap
    vector<vector<int>> dist(N, vector<int>(N, INF));

    // dist,
    for (int x = 1; x < N; ++x)
        PQ.push({dist[x][0] = UF.Size(x * N + 0), x, 0});
    for (int y = 1; y < N - 1; ++y)
        PQ.push({dist[N - 1][y] = UF.Size((N - 1) * N + y), N - 1, y});

    while (PQ.size())
    {
        auto [cdist, x, y] = PQ.top();
        PQ.pop();
        if (dist[x][y] != cdist)
            continue;

        if (x == 0 || y == N - 1)
        {
            cout << cdist << '\n'; // µµÂø
            break;
        }

        for (int d = 0; d < 8; ++d)
        {
            const int nx = x + "10001222"[d] - '1';
            const int ny = y + "22100012"[d] - '1';
            if (nx < 0 || nx >= N || ny < 0 || ny >= N)
                continue;
            if (Map[nx][ny] == '.')
                continue;
            const int cost = UF.Find(x * N + y) != UF.Find(nx * N + ny) ? UF.Size(nx * N + ny) : 0;
            if (dist[nx][ny] > cdist + cost)
                PQ.push({dist[nx][ny] = cdist + cost, nx, ny});
        }
    }

    return 0;
}