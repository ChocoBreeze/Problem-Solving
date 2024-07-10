#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

// 왜 방향마다 저장할 생각을 못했을까..
vector<vector<vector<int>>> visited; // 각 좌표까지 최단 거리 저장
vector<vector<string>> Map;          // 회전 횟수 당 Map
// vector<string> Map;

struct QData
{
    int x, y;      // 좌표
    int rotateCnt; // 회전 횟수
    QData(int x, int y, int c) : x(x), y(y), rotateCnt(c) {}
};

struct coord
{
    int x, y;
    coord(int x, int y) : x(x), y(y) {}
};

int dx[]{-1, 1, 0, 0, 0};
int dy[]{0, 0, -1, 1, 0};

coord start(0, 0);

int main()
{
    cin.tie(NULL)->sync_with_stdio(false);
    int k;
    cin >> k;
    const int SIZE = 4 * k;
    Map.assign(4, vector<string>(SIZE, ""));
    visited.assign(4, vector<vector<int>>(SIZE, vector<int>(SIZE, 0)));

    for (int i = 0; i < SIZE; ++i)
    {
        cin >> Map[0][i];
        Map[1][i] = Map[2][i] = Map[3][i] = Map[0][i];
        for (int j = 0; j < SIZE; ++j)
        {
            if (Map[0][i][j] == 'S')
            {
                start.x = i, start.y = j;
            }
        }
    }

    // 각 회전횟수 당 배열 만들기
    for (int r{1}; r < 4; ++r)
    {
        for (int i = 0; i < SIZE; i += 4)
        {
            for (int j = 0; j < SIZE; j += 4)
            {
                int X = (i / 4) * 4, Y = (j / 4) * 4;
                for (int x = 0; x < 4; ++x)
                {
                    for (int y = 0; y < 4; ++y)
                    {
                        Map[r][X + x][Y + y] = Map[r - 1][X + 3 - y][Y + x];
                    }
                }
            }
        }
    }

    queue<QData> q;
    q.push(QData(start.x, start.y, 0));
    visited[0][start.x][start.y] = 1;

    while (!q.empty())
    {
        QData now = q.front();
        q.pop();
        int startX = (now.x / 4) * 4, startY = (now.y / 4) * 4;
        // cout << "x : " << now.x << " y : " << now.y << " rotate : " << now.rotateCnt << " time : " << now.time <<  "\n";

        if (Map[now.rotateCnt][now.x][now.y] == 'E')
        {
            cout << visited[now.rotateCnt][now.x][now.y] - 1 << '\n';
            return 0;
        }

        // 확장
        for (int i = 0; i < 5; ++i)
        {
            int nx = now.x + dx[i];
            int ny = now.y + dy[i];
            if (nx < 0 || ny < 0 || nx >= SIZE || ny >= SIZE)
                continue; // 범위
            int startNX = (nx / 4) * 4;
            int startNY = (ny / 4) * 4;
            int rotateNX = startNX + (ny % 4);
            int rotateNY = startNY + 3 - (nx % 4);
            if (startX == startNX && startY == startNY)
            { // 새좌표가 같은 영역
                if (Map[now.rotateCnt][nx][ny] == '#')
                    continue; // 벽
                if (visited[(now.rotateCnt + 1) % 4][rotateNX][rotateNY] &&
                    visited[(now.rotateCnt + 1) % 4][rotateNX][rotateNY] <= visited[now.rotateCnt][now.x][now.y] + 1)
                    continue; // 갈 필요 없음
                visited[(now.rotateCnt + 1) % 4][rotateNX][rotateNY] = visited[now.rotateCnt][now.x][now.y] + 1;
                q.push(QData(rotateNX, rotateNY, (now.rotateCnt + 1) % 4)); // 회전 카운팅 유지
            }
            else
            { // 새 좌표가 다른 영역
                if (Map[0][nx][ny] == '#')
                    continue; // 벽
                if (visited[1][rotateNX][rotateNY] &&
                    visited[1][rotateNX][rotateNY] <= visited[now.rotateCnt][now.x][now.y] + 1)
                    continue; // 갈 필요 없음
                visited[1][rotateNX][rotateNY] = visited[now.rotateCnt][now.x][now.y] + 1;
                q.push(QData(rotateNX, rotateNY, 1)); // 새 회전
            }
        }
    }

    cout << "-1\n";
    return 0;
}