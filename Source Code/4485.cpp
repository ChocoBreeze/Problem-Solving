#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct coord {
	int x;
	int y;
	coord(int x, int y) : x(x), y(y) {}
};

vector<int> dx = { -1,1,0,0 };
vector<int> dy = { 0,0,-1,1 };

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	int N;
	for(int tc=1;;++tc) {
		cin >> N;
		if (!N) break;
		vector<vector<int>> m(N, vector<int>(N, 0));
		for (auto& i : m) {
			for (auto& j : i) {
				cin >> j;
			}
		}
		vector<vector<int>> dist(N, vector<int>(N, 1000000)); // 125 * 125 * 9 
		queue<coord> PQ; 
		dist[0][0] = m[0][0];
		PQ.push(coord(0, 0));
		while (!PQ.empty()) {
			coord now = PQ.front();
			PQ.pop();
			for (int i = 0; i < 4; ++i) {
				int nx = now.x + dx[i], ny = now.y + dy[i];
				if (nx >= 0 && nx < N && ny >= 0 && ny < N) {
					if (dist[nx][ny] > dist[now.x][now.y] + m[nx][ny]) {
						dist[nx][ny] = dist[now.x][now.y] + m[nx][ny];
						PQ.push(coord(nx, ny));
					}
				}
			}
		}
		cout << "Problem " << tc << ": " << dist[N - 1][N - 1] << "\n";
	}
	return 0;
}