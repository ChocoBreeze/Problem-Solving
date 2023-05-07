// UnionFind
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
#include <set>

#define FASTIO cin.tie(NULL)->sync_with_stdio(false)

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
            return false; // a == b
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
        return a == b;
    }
};

struct coord
{
    int x, y;
    coord(int x, int y) : x(x), y(y) {}
    coord() = default;
};

coord swan1(-1, -1), swan2(-1, -1);
int swan1Index, swan2Index;

int R, C;
vector<string> Map;
// 각 Union마다 경계 정보를 update하려고 했으나 굳이 그럴 필요 없었음..
vector<vector<int>> visited; // 단순히 visited 정보만 저장(어느 union에 속했는지는 저장할 필요 X)

inline int CoordToIndex(coord &&c)
{
    return C * c.x + c.y;
}

void UnionLakeAndMelt(UnionFind &uf, coord &&start, queue<coord> &willMelt)
{
    queue<coord> Q;
    visited[start.x][start.y] = 1;
    Q.push(start);
    while (!Q.empty())
    {
        coord now = Q.front();
        Q.pop();

        for (int d{}; d < 4; ++d)
        {
            int nx = now.x + "0211"[d] - '1';
            int ny = now.y + "1102"[d] - '1';

            if (nx < 0 || nx >= R || ny < 0 || ny >= C)
                continue;
            if (visited[nx][ny])
                continue;
            visited[nx][ny] = 1;

            if (Map[nx][ny] == '.' || Map[nx][ny] == 'L')
            { // L이 늦게 갱신될 수 있음.
                Q.push(coord(nx, ny));
                uf.Union(CoordToIndex(move(now)), CoordToIndex(coord(nx, ny)));
            }
            else if (Map[nx][ny] == 'X')
            {
                willMelt.push(coord(nx, ny));
                // Map[nx][ny] = '.'; // 바로 녹는 것이 아니기 때문에 나중에 갱신
            }
        }
    }
}

int main()
{
    FASTIO;
    // freopen("labudovi.i05", "r", stdin);
    cin >> R >> C;
    UnionFind uf(R * C);
    Map = vector<string>(R);
    visited.assign(R, vector<int>(C, 0));

    // input
    for (int r{}; r < R; ++r)
    {
        cin >> Map[r];
    }

    // 처음 호수 정보 확인 후 녹을 얼음 갱신
    queue<coord> willMelt;
    for (int r{}; r < R; ++r)
    {
        for (int c{}; c < C; ++c)
        {
            if (Map[r][c] == 'L')
            {
                if (swan1.x == -1 && swan1.y == -1)
                    swan1 = {r, c};
                else
                    swan2 = {r, c};
                Map[r][c] = '.';
            }
            if (Map[r][c] == '.' && !visited[r][c])
            {
                UnionLakeAndMelt(uf, coord(r, c), willMelt);
            }
        }
    }

    swan1Index = CoordToIndex(move(swan1)), swan2Index = CoordToIndex(move(swan2));
    int time{1};

    for (; !uf.IsSame(swan1Index, swan2Index); ++time)
    {
        int siz = static_cast<int>(willMelt.size());
        while (siz--)
        {
            coord now = willMelt.front();
            willMelt.pop();
            Map[now.x][now.y] = '.';

            for (int d{}; d < 4; ++d)
            {
                int nx = now.x + "0211"[d] - '1';
                int ny = now.y + "1102"[d] - '1';

                if (nx < 0 || nx >= R || ny < 0 || ny >= C)
                    continue;
                if (Map[nx][ny] == '.')
                { // 바로 union 가능 - 이 경우에 visited여도 합쳐야 함.!!
                    uf.Union(CoordToIndex(move(now)), CoordToIndex(coord(nx, ny)));
                }

                if (visited[nx][ny])
                    continue;
                visited[nx][ny] = 1;

                if (Map[nx][ny] == 'X')
                { // willMelt
                    willMelt.push(coord(nx, ny));
                    // Map[nx][ny] = '.'; // 바로 녹는 것이 아니기 때문에 나중에 갱신
                }
            }
        }
    }

    cout << time - 1 << '\n';

    return 0;
}