// 검은 방(0)은 들어갈 수 없음
// 몇 개의 검은 방을 뚫어야 도달을 할 수 있을까?

#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

int dx[]{ -1,1,0,0 };
int dy[]{ 0,0,-1,1 };
const int INF = static_cast<int>(21e8);

struct Edge {
	int x, y; // 위치
	int cnt; // 벽 뚫은 횟수
	Edge(int x, int y, int cnt) : x(x), y(y), cnt(cnt) {}
	bool operator<(const Edge& other) const { // min heap
		return cnt > other.cnt;
	}
};

int main() {
	int N;
	cin >> N;
	vector<string> Map(N,"");
	for (string& s : Map) {
		cin >> s;
	}

	// 1이 흰방
	vector<vector<int>> dist(N, vector<int>(N, INF)); // 벽 뚫은 횟수
	priority_queue<Edge> pq;
	dist[0][0] = 0;
	pq.push(Edge(0, 0, 0));

	while (!pq.empty()) {
		auto now = pq.top();
		pq.pop();

		if (dist[now.x][now.y] < now.cnt) continue; // 볼 필요 없음

		// 방향 배열로~
		for (int d = 0; d < 4; ++d) {
			int nx = now.x + dx[d];
			int ny = now.y + dy[d];

			if (nx < 0 || ny < 0 || nx >= N || ny >= N) continue; // 절대 범위를 확인 하지마!
			if (dist[nx][ny] <= dist[now.x][now.y]) continue; // 볼 필요 없음

			if (Map[nx][ny] == '0') dist[nx][ny] = dist[now.x][now.y] + 1; // 검은 방
			else dist[nx][ny] = dist[now.x][now.y]; // 흰 방
			pq.push(Edge(nx, ny, dist[nx][ny])); // 빼먹었군.

		}
	}
	cout << dist[N - 1][N - 1] << endl;
	return 0;
}