#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

struct coord
{
    int x, y;
    coord(int x, int y) : x(x), y(y) {}
};

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);
    int T{};
    cin >> T;
    for (int t{}; t < T; ++t)
    {
        int H{}, W{}, answer{};
        cin >> H >> W;
        vector<string> Map(H, "");
        vector<vector<bool>> visited(H, vector<bool>(W, 0));
        vector<queue<coord>> Qs(27, queue<coord>());
        vector<bool> haveKeys(27, false); // a : 1 ~

        for (string &s : Map)
            cin >> s;
        string key;
        cin >> key;
        if (key != "0")
        {
            for (char &k : key)
            {
                int idx = k - 'a' + 1;
                haveKeys[idx] = true;
            }
        }

        for (int h{}; h < H; ++h)
        {
            for (int w{}; w < W; ++w)
            {
                if (!(h == 0 || h == H - 1 || w == 0 || w == W - 1))
                    continue; // border
                if (Map[h][w] == '*')
                    continue; // º®
                if (Map[h][w] == '.' || Map[h][w] == '$')
                    Qs[0].push(coord(h, w));
                if ('a' <= Map[h][w] && Map[h][w] <= 'z')
                {
                    int idx = Map[h][w] - 'a' + 1;
                    haveKeys[idx] = true;
                    while (!Qs[idx].empty())
                    {
                        coord nowCanGo = Qs[idx].front();
                        Qs[idx].pop();
                        Qs[0].push(nowCanGo);
                    }
                    Qs[0].push(coord(h, w));
                }
                if ('A' <= Map[h][w] && Map[h][w] <= 'Z')
                { // Door
                    int idx = Map[h][w] - 'A' + 1;
                    if (haveKeys[idx])
                        Qs[0].push(coord(h, w));
                    else
                        Qs[idx].push(coord(h, w));
                }
                visited[h][w] = 1;
            }
        }

        while (!Qs[0].empty())
        {
            coord now = Qs[0].front();
            Qs[0].pop();

            if (Map[now.x][now.y] == '$')
                ++answer;

            for (int dir{}; dir < 4; ++dir)
            {
                int nx = now.x + "0211"[dir] - '1';
                int ny = now.y + "1102"[dir] - '1';
                if (nx < 0 || nx >= H || ny < 0 || ny >= W)
                    continue;
                if (Map[nx][ny] == '*')
                    continue; // wall
                if (visited[nx][ny])
                    continue;
                visited[nx][ny] = true;
                if ('a' <= Map[nx][ny] && Map[nx][ny] <= 'z')
                {                                    // key
                    int idx = Map[nx][ny] - 'a' + 1; // a : 1 ~
                    haveKeys[idx] = 1;
                    while (!Qs[idx].empty())
                    {
                        coord nowCanGo = Qs[idx].front();
                        Qs[idx].pop();
                        Qs[0].push(nowCanGo);
                    }
                    Qs[0].push(coord(nx, ny));
                }
                else if ('A' <= Map[nx][ny] && Map[nx][ny] <= 'Z')
                {                                    // door
                    int idx = Map[nx][ny] - 'A' + 1; // A : 1 ~
                    if (haveKeys[idx])
                        Qs[0].push(coord(nx, ny));
                    else
                        Qs[idx].push(coord(nx, ny));
                }
                else // 0 or DOC
                {
                    Qs[0].push(coord(nx, ny));
                }
            }
        }
        cout << answer << '\n';
    }
    return 0;
}