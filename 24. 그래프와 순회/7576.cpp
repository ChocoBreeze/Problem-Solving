// 종료 조건
#include<iostream>
#include<vector>
#include<queue>
#include<utility>

using std::cin;
using std::cout;
using std::vector;
using std::queue;
using std::pair; // <utility>
using std::make_pair;

int main() {
	cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	int N, M, cnt_m_ones = 0, cnt_ones = 0;
	cin >> M >> N;
	vector<vector<int>> tomatoes(N, vector<int>(M, 0));
	queue<pair<int, int>> Q;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			cin >> tomatoes[i][j];
			if (tomatoes[i][j] == 1) {
				Q.push(make_pair(i, j));
				++cnt_ones;
			}
			else if (tomatoes[i][j] == -1) ++cnt_m_ones;
		}
	}
	int goals = N * M - cnt_m_ones, answer;
	if (goals == cnt_ones) {
		std::cout << 0;
		return 0;
	}
	for (answer = 1;; ++answer) {
		int cnt_ones_now = cnt_ones;
		queue<pair<int, int>> Q_temp;
		while (!Q.empty()) {
			auto now = Q.front();
			Q.pop();
			if (now.first >= 1 && tomatoes[now.first - 1][now.second] == 0) { // up
				Q_temp.push(make_pair(now.first - 1, now.second));
				tomatoes[now.first - 1][now.second] = 1;
				++cnt_ones;
			}
			if (now.first < N - 1 && tomatoes[now.first + 1][now.second] == 0) { // down
				Q_temp.push(make_pair(now.first + 1, now.second));
				tomatoes[now.first + 1][now.second] = 1;
				++cnt_ones;
			}
			if (now.second >= 1 && tomatoes[now.first][now.second - 1] == 0) { // left
				Q_temp.push(make_pair(now.first, now.second - 1));
				tomatoes[now.first][now.second - 1] = 1;
				++cnt_ones;
			}
			if (now.second < M - 1 && tomatoes[now.first][now.second + 1] == 0) { // right
				Q_temp.push(make_pair(now.first, now.second + 1));
				tomatoes[now.first][now.second + 1] = 1;
				++cnt_ones;
			}
		}
		if (cnt_ones == goals) { // 토마토 다 익음
			std::cout << answer;
			break;
		}
		if (cnt_ones_now == cnt_ones) {
			std::cout << -1;
			break;
		}
		while (!Q_temp.empty()) {
			Q.push(Q_temp.front());
			Q_temp.pop();
		}
	}
	return 0;
}