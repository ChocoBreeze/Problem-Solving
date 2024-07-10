// 연구소의 바이러스 M개를 활성 상태로 변경하려 함
// 연구소의 크기는 N x N
// 모든 칸에 바이러스를 퍼뜨리기
// 0은 빈 칸, 1은 벽, 2는 바이러스를 놓을 수 있는 위치

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;
constexpr int INF = static_cast<int>(21e8);

struct coord {
	int x, y;
	coord(int x, int y) : x(x), y(y) {}
};

int N, M;
int ans = INF;
int goal; // 먹어야 하는 빈 칸
vector<vector<int>> Map;
vector<coord> viruses;
vector<int> selected;

// virus를 M개 뽑은 후 simulation 진행 -> 최소 시간 갱신
// flood fill
int Simulation() {
	int time{}, cnt{}; // 시간, 얼마나 빈 칸을 먹었는지
	vector<vector<int>> visited(N, vector<int>(N, 0));
	queue<coord> q;
	for (int& s : selected) {
		q.push(coord(viruses[s].x, viruses[s].y));
		visited[viruses[s].x][viruses[s].y] = 1; // 방문 완료
	}

	int dx[]{ -1,1,0,0 };
	int dy[]{ 0,0,-1,1 };

	while (!q.empty()) {
		if (cnt >= goal) break; // 이미 빈 공간이 없어요
		if (time >= ans) return INF; // 더 해볼 필요 없어요
		int cursize = q.size();
		for (int ss{}; ss < cursize; ++ss) { // 퍼질 수 있는 만큼 퍼지기
			coord now = q.front();
			q.pop();

			int& nowVisited = visited[now.x][now.y];
			for (int i{}; i < 4; ++i) {
				int nx = now.x + dx[i];
				int ny = now.y + dy[i];

				if (nx < 0 || ny < 0 || nx >= N || ny >= N) continue; // 히히 못 가
				if (visited[nx][ny]) continue; // 이미 감
				if (Map[nx][ny] == 1) continue; // 벽

				visited[nx][ny] = nowVisited + 1;
				q.push(coord(nx, ny));
				if (!Map[nx][ny]) ++cnt; // Map[nx][ny] == 0
			}
		}
		time++;
	}
	// q가 empty인데 다 못먹는 경우도 있구나
	if (cnt >= goal) return time; // 빈 공간이 없음
	else return INF;
}

// M개의 virus 조합 만들기
void makeCombination(int now) {
	if (selected.size() == M) { // base case
		ans = min(ans, Simulation());
		return;
	}
	if (now == viruses.size()) return;  // base case

	for (int i{ now }; i < static_cast<int>(viruses.size()); ++i) {
		selected.push_back(i);
		makeCombination(i + 1);
		selected.pop_back();
	}
}

void solve() {
	// virus M개 조합 만들기
	makeCombination(0);
}

int main() {
	cin.tie(NULL)->sync_with_stdio(false);
	
	cin >> N >> M;
	Map.assign(N, vector<int>(N, 0));
	for (int i{}; i < N; ++i) {
		for (int j{}; j < N; ++j) {
			cin >> Map[i][j];
			if (Map[i][j] == 2) {
				viruses.push_back(coord(i, j));
				// Map[i][j] = 0;
			}
			else if (!Map[i][j]) { // 빈 칸 카운팅
				goal++;
			}
		}
	}
	
	solve();
	if (ans == INF) ans = -1;
	cout << ans << '\n';
	
	return 0;
}