// 아이디어 생각하기. (길을 막기 위한 아이디어!)
// 굳이 그래프 간선을 만들 필요 없이 기존 맵에서도 가능했음!
// 164ms
#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

int N{}, counting{};
constexpr int INF = static_cast<int>(21e8);

vector<string> strMap;   // input
vector<vector<int>> Map; // input -> index
vector<int> spaces;      // index별 차지하는 공간 개수

struct coord
{
    int x, y;
    coord(int x, int y) : x(x), y(y) {}
};

struct Edge
{
    coord c;
    int weight;
    Edge(coord c, int weight) : c(c), weight(weight) {}
    bool operator<(const Edge &other) const
    { // min heap
        return this->weight > other.weight;
    }
};

// 상하좌우 대각선
int dx[]{-1, 1, 0, 0, -1, -1, 1, 1};
int dy[]{0, 0, -1, 1, -1, 1, 1, -1};

void Bfs(coord start)
{
    queue<coord> q;
    q.push(start);
    int count{1};                     // 영역 개수
    Map[start.x][start.y] = counting; // index - built-in function ‘index’
    char startChar = strMap[start.x][start.y];
    while (!q.empty())
    {
        coord now = q.front();
        q.pop();

        // 상하좌우
        for (int dir{}; dir < 4; ++dir)
        {
            int nx = now.x + dx[dir];
            int ny = now.y + dy[dir];
            if (nx < 0 || ny <= 0 || nx >= N || ny > N)
                continue;
            if (Map[nx][ny] == -1 && strMap[nx][ny] == startChar)
            {
                q.push(coord(nx, ny));
                Map[nx][ny] = counting;
                ++count;
            }
        }
    }
    spaces.push_back(count);
    ++counting;
}

int main()
{
    cin.tie(NULL)->sync_with_stdio(false);
    cin >> N;
    strMap.assign(N, "");
    Map.assign(N + 1, vector<int>(N + 1, -1));
    for (int n{}; n < N; ++n)
    {
        string temp;
        cin >> temp;
        strMap[n] = " " + temp;
    }

    for (int i{}; i < N; ++i)
    {
        for (int j{1}; j <= N; ++j)
        {
            if (strMap[i][j] == '.')
                continue;
            if (Map[i][j] != -1)
                continue;
            Bfs(coord(i, j));
        }
    }

    priority_queue<Edge> PQ;
    vector<vector<int>> dist(N + 1, vector<int>(N + 1, INF)); // 2D
    dist[N][0] = 0;                                           // start
    PQ.push(Edge(coord(N, 0), 0));

    // 그래프 밖에서 시작해도 된다!
    // 꼭 간선 정보를 만들지 않아도 된다!

    auto inside2 = [](int x, int y) -> bool
    {
        return 0 <= x && x <= N && 0 <= y && y <= N;
    };

    auto RandJ = [](int x, int y) -> bool
    {
        return (x == 0 && y == 1) || (x == N - 1 && y == N);
    };

    while (!PQ.empty())
    {
        Edge now = PQ.top();
        PQ.pop();
        // 도착점 (행이 0 or 열이 N-1)
        if (Map[now.c.x][now.c.y] != -1 && (now.c.x == 0 || now.c.y == N))
        {
            cout << now.weight << '\n';
            break;
        }

        if (dist[now.c.x][now.c.y] != now.weight)
            continue;

        for (int dir{}; dir < 8; ++dir)
        {
            int nx = now.c.x + dx[dir];
            int ny = now.c.y + dy[dir];
            if (RandJ(nx, ny))
                continue;
            if (!inside2(nx, ny))
                continue;
            int nw{};
            if (Map[nx][ny] == -1)
                nw = 0;
            else
                nw = Map[now.c.x][now.c.y] == Map[nx][ny] ? 0 : spaces[Map[nx][ny]];
            if (dist[nx][ny] > now.weight + nw)
            {
                dist[nx][ny] = now.weight + nw;
                PQ.push(Edge(coord(nx, ny), dist[nx][ny]));
            }
        }
    }

    return 0;
}