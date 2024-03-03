// Minimum Cut = Maximum Flow
// Maximum Flow - Dinic(O(V^2E))
// https://m.blog.naver.com/kks227/220812858041
// Adjacency Matrix(200ms)

/*
level graph : 모든 정점에 대해 소스에서부터의 최단거리(거쳐야 하는 간선 개수)를 레벨 값으로 매겨놓은 그래프
- src(0)을 기준으로 인접한 정점들(1), 그와 인접한 정점들(2), ...
- 여유 용량(residual)이 없는 간선은 사용할 수 없다.
blocking flow : 레벨 그래프에서는 원래의 그래프에서 간선 (u, v)가 존재하더라도, v의 레벨이 u의 레벨보다 정확히 1 클 때만 이동 가능하다.
- 즉, 항상 인접하면서 자신보다 레벨이 1 큰 정점으로만 이동 가능하다.
- 이런 그래프에서 더 이상 소스에서 싱크로 흘릴 수 있는 유량이 없게 만드는 유량 상태.

(1) 레벨 그래프 만들기 - 이 때 싱크에 도달할 수 없다면 종료
(2) 레벨 그래프에서 blocking flow를 찾아 그만큼을 총 유량에 더하고 (1)로 돌아가기
*/

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

constinit const int MAXN = 500;
constinit const int SIZE = MAXN + 2;
constinit const int SRC = SIZE - 2;
constinit const int SINK = SIZE - 1;
constinit const int INF = 1'000'000'000;

int N, c[SIZE][SIZE]{}, f[SIZE][SIZE]{}; // c : capacity, f : flow
int level[SIZE]{}; // 레벨 그래프에서 정점의 레벨(SRC가 0)
int work[SIZE]{}; // dfs 중, 이 정점이 몇 번째 간선까지 탐색했는지 기억하는 용도
vector<int> adj[SIZE]{};

// 디닉 전용 bfs 함수
bool bfs() {
    // 레벨값 초기화
    fill(level, level + SIZE, -1);
    level[SRC] = 0;

    queue<int> Q;
    Q.push(SRC);
    while (!Q.empty()) {
        int curr = Q.front(); Q.pop();
        for (int& next : adj[curr]) {
            // 레벨값이 설정되지 않았고, 간선에 residual이 있을 때만 이동
            if (level[next] == -1 && c[curr][next] - f[curr][next] > 0) {
                level[next] = level[curr] + 1; // next의 레벨은 curr의 레벨 + 1
                Q.push(next);
            }
        }
    }
    // 싱크에 도달 가능하면 true, 아니면 false를 리턴
    return (level[SINK] != -1);
}

// 디닉 전용 dfs 함수: curr에서 dest까지 최대 flow만큼의 유량을 보낼 것
int dfs(int curr, int dest, int flow) {
    // base case: dest에 도달함
    if (curr == dest) return flow;

    // 현재 정점에서 인접한 정점들을 탐색
    // 이때, 이번 단계에서 이미 쓸모없다고 판단한 간선은 다시 볼 필요가 없으므로
    // work 배열로 간선 인덱스를 저장해 둠
    for (int& i = work[curr]; i < adj[curr].size(); i++) {
        int& next = adj[curr][i];
        // next의 레벨이 curr의 레벨 + 1이고, 간선에 residual이 남아있어야만 이동
        if (level[next] == level[curr] + 1 && c[curr][next] - f[curr][next] > 0) {
            // df: flow와 다음 dfs함수의 결과 중 최소값
            // 결과적으로 경로상의 간선들 중 가장 작은 residual이 됨
            int df = dfs(next, dest, min(c[curr][next] - f[curr][next], flow));
            // 증가 경로가 있다면, 유량을 df만큼 흘리고 종료
            if (df > 0) {
                f[curr][next] += df;
                f[next][curr] -= df;
                return df;
            }
        }
    }
    // 증가 경로를 찾지 못함: 유량 0 흘림
    return 0;
}

int main() {
    // 그래프 정보 입력받기
    cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
    cin >> N;
    for (int i{}; i < N; ++i) {
        int team; cin >> team;
        if (team == 1) {
            c[SRC][i] = INF;
            adj[SRC].push_back(i);
            adj[i].push_back(SRC);
        }
        else if (team == 2) {
            c[i][SINK] = INF;
            adj[i].push_back(SINK);
            adj[SINK].push_back(i);
        }
    }
    for (int i{}; i < N; ++i) {
        for (int j{}; j < N; ++j) {
            cin >> c[i][j];
            if (c[i][j] == 0) continue; // 0인 간선 제외 - 이 코드 주석 처리 시 376ms
            if (i != j) adj[i].push_back(j);
        }
    }

    // 디닉 알고리즘 수행
    int total{};
    // 레벨 그래프를 구축하여 싱크가 도달 가능한 동안 반복
    while (bfs()) {
        fill(work, work + SIZE, 0);
        // 차단 유량(blocking flow) 구하기
        while (1) {
            int flow = dfs(SRC, SINK, INF); // dfs를 사용해 각 경로를 찾음
            if (flow == 0) break; // 더 이상 경로가 없으면 종료
            total += flow; // 총 유량에 이번에 구한 유량 더함
        }
    }
    cout << total << '\n';

    // 각 진영에 속한 사람을 판단하기 위해 소스에서의 도달가능성 판별
    vector<bool> visited(SIZE, false);
    visited[SRC] = true;
    queue<int> Q;
    Q.push(SRC);
    while (!Q.empty()) {
        int curr = Q.front(); Q.pop();
        for (int& next : adj[curr]) {
            // 여유 용량이 남아있는 간선만을 이용
            if (!visited[next] && c[curr][next] - f[curr][next] > 0) {
                visited[next] = true;
                Q.push(next);
            }
        }
    }

    // A진영에 속한 사람들: 소스에서 도달 가능
    // B진영에 속한 사람들: 소스에서 도달 불가능
    vector<int> groupA, groupB;
    groupA.reserve(N), groupB.reserve(N);
    for (int i{}; i < N; ++i) {
        if (visited[i]) groupA.push_back(i + 1);
        else groupB.push_back(i + 1);
    }

    auto Print = [](const vector<int>& vec) {
        for (auto& v : vec) cout << v << ' ';
        cout << '\n';
        };

    Print(groupA);
    Print(groupB);
    return 0;
}