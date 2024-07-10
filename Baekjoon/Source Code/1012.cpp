#include<iostream>
#include<queue>
#include<vector>

using std::cin;
using std::cout;
using std::vector;
using std::queue;
using std::pair;
using std::make_pair;

void bfs(vector<vector<int>>& map, int j, int k) {
	queue < pair<int, int>> Q;
	Q.push(make_pair(j, k));
	map[j][k] = 0;
	int N = map.size(), M = map[0].size();
	while (!Q.empty()) {
		auto i = Q.front();
		Q.pop();
		if (i.first >= 1 && map[i.first - 1][i.second] == 1) { // up
			Q.push(make_pair(i.first - 1, i.second));
			map[i.first - 1][i.second] = 0;
		}
		if (i.first < N - 1 && map[i.first + 1][i.second] == 1) { // down
			Q.push(make_pair(i.first + 1, i.second));
			map[i.first + 1][i.second] = 0;
		}
		if (i.second >= 1 && map[i.first][i.second - 1] == 1) { // 
			Q.push(make_pair(i.first, i.second - 1));
			map[i.first][i.second - 1] = 0;
		}
		if (i.second < M - 1 && map[i.first][i.second + 1] == 1) {
			Q.push(make_pair(i.first, i.second + 1));
			map[i.first][i.second + 1] = 0;
		}
	}
}

int main() {
	cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	int T, M, N, K, X, Y; // 가로 M, 세로 N
	cin >> T;
	for (int i = 0; i < T; ++i) {
		cin >> M >> N >> K;
		vector<vector<int>> map(N, vector<int>(M, 0));
		for (int j = 0; j < K; ++j) {
			cin >> X >> Y;
			map[Y][X] = 1;
		}
		int cnt = 0;
		for (int j = 0; j < N; ++j) {
			for (int k = 0; k < M; ++k) {
				if (map[j][k] == 1) {
					bfs(map, j, k);
					++cnt;
				}
			}
		}
		cout << cnt << "\n";
	}
	return 0;
}