#include <iostream>
#include <vector>
#include <queue>
#include <utility> // pair

#define FASTIO cin.tie(nullptr)->sync_with_stdio(false)

using namespace std;
int R, C;
int countOne; // 1개수

void Bfs(vector<vector<int>> &Map, pair<int, int> start)
{
    queue<pair<int, int>> q;
    q.push(start);

    while (!q.empty())
    {
        pair<int, int> now = q.front();
        q.pop();
        for (int d{}; d < 4; ++d)
        {
            int nx = now.first + "0211"[d] - '1';  // -1,1,0,0
            int ny = now.second + "1102"[d] - '1'; // 0,0,-1,1
            if (nx < 1 || ny < 1 || nx > R || ny > C)
                continue; // hihi can't go
            if (Map[nx][ny] == 0)
            {
                q.push(make_pair(nx, ny));
                Map[nx][ny] = 2;
            }
        }
    }
}

int main()
{
    FASTIO;
    cin >> R >> C;                                         // 최대 100
    vector<vector<int>> Map(R + 2, vector<int>(C + 2, 2)); // [1 ~ R][1 ~ C]

    for (int i{1}; i <= R; ++i)
    {
        for (int j{1}; j <= C; ++j)
        {
            cin >> Map[i][j];
            if (Map[i][j])
                ++countOne;
        }
    }

    for (int i{0}; i <= R + 1; ++i)
    {
        for (int j{0}; j <= C + 1; ++j)
        {
            if (Map[i][j] == 2)
            {
                Bfs(Map, make_pair(i, j)); // 가장자리 확장
            }
        }
    }

    int time{};
    vector<int> countOnes{countOne};
    queue<pair<int, int>> newBorders;
    for (;; ++time)
    {
        vector<vector<int>> newMap(begin(Map), end(Map));
        for (int x{1}; x <= R; ++x)
        {
            for (int y{1}; y <= C; ++y)
            {
                if (Map[x][y] == 1)
                {
                    bool isBorder{false};
                    for (int d{}; d < 4; ++d)
                    {
                        int nx = x + "0211"[d] - '1'; // -1,1,0,0
                        int ny = y + "1102"[d] - '1'; // 0,0,-1,1
                        if (nx < 1 || ny < 1 || nx > R || ny > C)
                            continue;
                        if (Map[nx][ny] == 2)
                        { // border
                            isBorder = true;
                            break;
                        }
                    }
                    if (isBorder)
                    {
                        newMap[x][y] = 2;
                        newBorders.push(make_pair(x, y));
                        --countOne;
                    }
                }
            }
        }

        Map.swap(newMap);
        if (!countOne)
            break; // all melt
        countOnes.push_back(countOne);
        while (!newBorders.empty())
        { // extend border
            pair<int, int> now = newBorders.front();
            newBorders.pop();
            Bfs(Map, now);
        }
    }

    cout << time + 1 << '\n'
         << countOnes.back() << '\n';
    return 0;
}