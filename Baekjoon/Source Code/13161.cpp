// Dinic's Algorithm
// https://blog.naver.com/jinhan814/222284335708
// https://www.acmicpc.net/source/29124077
// Edmonds-Karp : O(V*E^2)
// Dinic : O(V^2*E)

// level graph : ��� ������ ���� �ҽ�(0)�������� �ִܰŸ�
// blocking flow : ���� �׷��������� ������ �׷������� ���� (u, v)�� �����ϴ���, v�� ������ u�� �������� ��Ȯ�� 1 Ŭ ���� �̵� �����ϴ�.

// level graph ����� - blocking flow �긮�� �ݺ�
// unitl ��ũ�� ������ �� ���� �� ����

#include <iostream>
#include <vector> 
#include <queue> 
#include <algorithm> // fill, min

using namespace std;

constinit const int INF = 1'000'000'000;

int N, SRC, SINK, SIZE;
vector<vector<int>> capacity, flow, adj;
vector<int> level, work;
// level : ���� �׷������� ������ ����(SRC�� 0)
// work : dfs ��, �� ������ �� ��° �������� Ž���ߴ��� ����ϴ� �뵵

// ��� ���� bfs �Լ�
bool bfs() {
    // ������ �ʱ�ȭ
    // fill(begin(level), end(level), -1);
    level.assign(SIZE, -1);
    level[SRC] = 0;

    queue<int> Q;
    Q.push(SRC);
    while (!Q.empty()) {
        int curr = Q.front(); Q.pop();
        for (int& next : adj[curr]) {
            // �������� �������� �ʾҰ�, ������ residual�� ���� ���� �̵�
            if (level[next] == -1 && capacity[curr][next] - flow[curr][next] > 0) {
                level[next] = level[curr] + 1; // next�� ������ curr�� ���� + 1
                Q.push(next);
            }
        }
    }
    // ��ũ�� ���� �����ϸ� true, �ƴϸ� false�� ����
    return (level[SINK] != -1);
}

// ��� ���� dfs �Լ�: curr���� dest���� �ִ� flow��ŭ�� ������ ���� ��
int dfs(int curr, int dest, int f) {
    if (curr == dest) return f; // base case: dest�� ������

    // ���� �������� ������ �������� Ž��
    // �̶�, �̹� �ܰ迡�� �̹� ������ٰ� �Ǵ��� ������ �ٽ� �� �ʿ䰡 �����Ƿ�
    // work �迭�� ���� �ε����� ������ ��
    for (int& i = work[curr]; i < adj[curr].size(); ++i) {
        int& next = adj[curr][i];
        // next�� ������ curr�� ���� + 1�̰�, ������ residual�� �����־�߸� �̵�
        if (level[next] == level[curr] + 1 && capacity[curr][next] - flow[curr][next] > 0) {
            // df: flow�� ���� dfs�Լ��� ��� �� �ּҰ�
            // ��������� ��λ��� ������ �� ���� ���� residual�� ��
            int df = dfs(next, dest, min(capacity[curr][next] - flow[curr][next], f));
            
            if (df > 0) { // ���� ��ΰ� �ִٸ�, ������ df��ŭ �긮�� ����
                flow[curr][next] += df;
                flow[next][curr] -= df;
                return df;
            }
        }
    }

    // ���� ��θ� ã�� ����: ���� 0 �긲
    return 0;
}

void AddEdge(int from, int to, int cap, bool direct = true) {
    adj[from].push_back(to);
    adj[to].push_back(from);
    capacity[from][to] += cap;
    if(!direct) capacity[to][from] += cap; // ����� �϶��� �߰�
}

int main() {
    // �׷��� ���� �Է¹ޱ�
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

    // ��� �˰��� ����
    int totalFlow{};
    // ���� �׷����� �����Ͽ� ��ũ�� ���� ������ ���� �ݺ�
    while (bfs()) {
        // fill(begin(work), end(work), 0);
        work.assign(SIZE, 0);
        // ���� ����(blocking flow) ���ϱ�
        while (1) {
            int f = dfs(SRC, SINK, INF); // dfs�� ����� �� ��θ� ã��
            if (f == 0) break; // �� �̻� ��ΰ� ������ ����
            totalFlow += f; // �� ������ �̹��� ���� ���� ����
        }
    }
    cout << totalFlow << '\n';

    // �� ������ ���� ����� �Ǵ��ϱ� ���� �ҽ������� ���ް��ɼ� �Ǻ�
    vector<bool> visited(SIZE, 0);
    visited[SRC] = true;
    queue<int> Q;
    Q.push(SRC);
    while (!Q.empty()) {
        int curr = Q.front(); Q.pop();
        for (int& next : adj[curr]) {
            // ���� �뷮�� �����ִ� �������� �̿�
            if (!visited[next] && capacity[curr][next] - flow[curr][next] > 0) {
                visited[next] = true;
                Q.push(next);
            }
        }
    }

    // A������ ���� �����: �ҽ����� ���� ����
    // B������ ���� �����: �ҽ����� ���� �Ұ���

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