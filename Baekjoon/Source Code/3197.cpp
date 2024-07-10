// https://hsin.hr/2005/index.html
// Not use UnionFind - only bfs
// 14276kb, 128ms
#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

struct coord
{
    int x, y;
    coord(int x, int y) : x(x), y(y) {}
};
coord swan1(-1, -1), swan2(-1, -1);

int main()
{
    cin.tie(NULL)->sync_with_stdio(false);

    int R, C;
    cin >> R >> C;
    vector<vector<char>> Map(R, vector<char>(C, 0));
    vector<vector<char>> meltVisited(R, vector<char>(C, 0));
    vector<vector<char>> swanVisited(R, vector<char>(C, 0));

    queue<coord> todayMelt, tomorrowMelt;
    queue<coord> todaySwan, tomorrowSwan;

    for (int r{}; r < R; ++r)
    {
        for (int c{}; c < C; ++c)
        {
            cin >> Map[r][c];
            if (Map[r][c] == 'L')
            {
                if (swan1.x == -1 && swan1.y == -1)
                    swan1 = {r, c};
                else
                    swan2 = {r, c};

                Map[r][c] = '.';
            }
            if (Map[r][c] == '.')
            {
                meltVisited[r][c] = 1;
                tomorrowMelt.push(coord(r, c));
            }
        }
    }

    todaySwan.push(swan1);
    swanVisited[swan1.x][swan1.y] = 1;

    int time{};
    for (; !swanVisited[swan2.x][swan2.y]; ++time)
    {
        // tomorrow -> today
        todayMelt.swap(tomorrowMelt);
        todaySwan.swap(tomorrowSwan);

        // ice melt
        while (!todayMelt.empty())
        {
            coord now = todayMelt.front();
            todayMelt.pop();
            Map[now.x][now.y] = '.';

            for (int d{}; d < 4; ++d)
            {
                int nx = now.x + "0211"[d] - '1';
                int ny = now.y + "1102"[d] - '1';
                if (nx < 0 || nx >= R || ny < 0 || ny >= C)
                    continue;
                if (meltVisited[nx][ny])
                    continue;

                meltVisited[nx][ny] = 1;
                tomorrowMelt.push(coord(nx, ny)); // 실제로 녹는 것은 내일
            }
        }

        // swan move
        while (!todaySwan.empty())
        {
            coord now = todaySwan.front();
            todaySwan.pop();
            for (int d{}; d < 4; ++d)
            {
                int nx = now.x + "0211"[d] - '1';
                int ny = now.y + "1102"[d] - '1';
                if (nx < 0 || nx >= R || ny < 0 || ny >= C)
                    continue;
                if (swanVisited[nx][ny])
                    continue;

                swanVisited[nx][ny] = 1;
                if (Map[nx][ny] == '.')
                    todaySwan.push(coord(nx, ny)); // 오늘 바로 갈 수 있음
                else
                    tomorrowSwan.push(coord(nx, ny)); // 내일되서 갈 수 있음
            }
        }
    }

    cout << time - 1 << '\n';
}