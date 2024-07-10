// Dinic's Algorithm
// https://blog.naver.com/jinhan814/222284335708
// https://www.acmicpc.net/source/29124077
// Edmonds-Karp : O(V*E^2)
// Dinic : O(V^2*E)

// level graph : 모든 정점에 대해 소스(0)에서부터 최단거리
// blocking flow : 레벨 그래프에서는 원래의 그래프에서 간선 (u, v)가 존재하더라도, v의 레벨이 u의 레벨보다 정확히 1 클 때만 이동 가능하다.

// level graph 만들기 - blocking flow 흘리기 반복
// unitl 싱크에 도달할 수 없을 때 까지

#include <iostream>
#include <vector> 
#include <queue> 
#include <algorithm> // fill, min

using namespace std;

constinit const int INF = 1'000'000'000;

int N, SRC, SINK, SIZE;
vector<vector<int>> capacity, flow, adj;
vector<int> level, work;
// level : 레벨 그래프에서 정점의 레벨(SRC가 0)
// work : dfs 중, 이 정점이 몇 번째 간선까지 탐색했는지 기억하는 용도

// 디닉 전용 bfs 함수
bool bfs() {
    // 레벨값 초기화
    // fill(begin(level), end(level), -1);
    level.assign(SIZE, -1);
    level[SRC] = 0;

    queue<int> Q;
    Q.push(SRC);
    while (!Q.empty()) {
        int curr = Q.front(); Q.pop();
        for (int& next : adj[curr]) {
            // 레벨값이 설정되지 않았고, 간선에 residual이 있을 때만 이동
            if (level[next] == -1 && capacity[curr][next] - flow[curr][next] > 0) {
                level[next] = level[curr] + 1; // next의 레벨은 curr의 레벨 + 1
                Q.push(next);
            }
        }
    }
    // 싱크에 도달 가능하면 true, 아니면 false를 리턴
    return (level[SINK] != -1);
}

// 디닉 전용 dfs 함수: curr에서 dest까지 최대 flow만큼의 유량을 보낼 것
int dfs(int curr, int dest, int f) {
    if (curr == dest) return f; // base case: dest에 도달함

    // 현재 정점에서 인접한 정점들을 탐색
    // 이때, 이번 단계에서 이미 쓸모없다고 판단한 간선은 다시 볼 필요가 없으므로
    // work 배열로 간선 인덱스를 저장해 둠
    for (int& i = work[curr]; i < adj[curr].size(); ++i) {
        int& next = adj[curr][i];
        // next의 레벨이 curr의 레벨 + 1이고, 간선에 residual이 남아있어야만 이동
        if (level[next] == level[curr] + 1 && capacity[curr][next] - flow[curr][next] > 0) {
            // df: flow와 다음 dfs함수의 결과 중 최소값
            // 결과적으로 경로상의 간선들 중 가장 작은 residual이 됨
            int df = dfs(next, dest, min(capacity[curr][next] - flow[curr][next], f));
            
            if (df > 0) { // 증가 경로가 있다면, 유량을 df만큼 흘리고 종료
                flow[curr][next] += df;
                flow[next][curr] -= df;
                return df;
            }
        }
    }

    // 증가 경로를 찾지 못함: 유량 0 흘림
    return 0;
}

void AddEdge(int from, int to, int cap, bool direct = true) {
    adj[from].push_back(to);
    adj[to].push_back(from);
    capacity[from][to] += cap;
    if(!direct) capacity[to][from] += cap; // 양방향 일때만 추가
}

int main() {
    // 그래프 정보 입력받기
    cin >> N;
    SRC = N;    SINK = N + 1;    SIZE = N + 2;

    capacity = vector(SIZE, vector<int>(SIZE,0)); // 
    flow = vector(SIZE, vector<int>(SIZE,0)); // 
    adj = vector(SIZE, vector<int>(0, 0)); // 

    for (int i{}; i < N; ++i) {
        int team; cin >> team;
        if (team == 1) AddEdge(SRC, i, INF); // direct
        else if(team == 2) AddEdge(i, SINK, INF); // direct
    }
    for (int i{}; i < N; ++i) {
        for (int j{}; j < N; ++j) {
            int cap{};  cin >> cap;
            if (i < j) AddEdge(i, j, cap, 0); // bidirect
        }
    }

    // 디닉 알고리즘 수행
    int totalFlow{};
    // 레벨 그래프를 구축하여 싱크가 도달 가능한 동안 반복
    while (bfs()) {
        // fill(begin(work), end(work), 0);
        work.assign(SIZE, 0);
        // 차단 유량(blocking flow) 구하기
        while (1) {
            int f = dfs(SRC, SINK, INF); // dfs를 사용해 각 경로를 찾음
            if (f == 0) break; // 더 이상 경로가 없으면 종료
            totalFlow += f; // 총 유량에 이번에 구한 유량 더함
        }
    }
    cout << totalFlow << '\n';

    // 각 진영에 속한 사람을 판단하기 위해 소스에서의 도달가능성 판별
    vector<bool> visited(SIZE, 0);
    visited[SRC] = true;
    queue<int> Q;
    Q.push(SRC);
    while (!Q.empty()) {
        int curr = Q.front(); Q.pop();
        for (int& next : adj[curr]) {
            // 여유 용량이 남아있는 간선만을 이용
            if (!visited[next] && capacity[curr][next] - flow[curr][next] > 0) {
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