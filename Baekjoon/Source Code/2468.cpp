#include<iostream>
#include<vector>
#include<queue>
#include<utility>
#include<algorithm>

using namespace std;

vector<int> dx = { -1, 1, 0, 0 };
vector<int> dy = { 0, 0, -1, 1 };
int N;

int depth_count(vector<vector<int>>& m, int depth) {
	int cnt = 0;
	vector<vector<bool>> chk(N, vector<bool>(N, false));
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			if (m[i][j] > depth && !chk[i][j]) {
				++cnt;
				queue<pair<int, int>> Q;
				Q.push(make_pair(i, j));
				chk[i][j] = true;
				while (!Q.empty()) {
					pair<int, int> now = Q.front();
					Q.pop();
					for (int k = 0; k < 4; ++k) {
						if (now.first + dx[k] >= 0 && now.first + dx[k] < N && now.second + dy[k] >= 0 && now.second + dy[k] < N) {
							if (m[now.first + dx[k]][now.second + dy[k]] > depth && !chk[now.first+dx[k]][now.second+dy[k]]) {
								chk[now.first + dx[k]][now.second + dy[k]] = true; // clear
								Q.push(make_pair(now.first + dx[k], now.second + dy[k]));
							}
						}
					}
				}
			}
		}
	}
	return cnt;
}

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	cin >> N;
	int min_d= 101, max_d=-1;
	vector<vector<int>> m(N,vector<int>(N,0));
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			cin >> m[i][j];
			if (max_d < m[i][j]) max_d = m[i][j];
			if (min_d > m[i][j]) min_d = m[i][j];
		}
	}
	int answer = 1; // 아무 지역도 안 잠김(
	for (int d = min_d; d < max_d; ++d) {
		answer = max(answer, depth_count(m, d));
	}
	cout << answer;
	return 0;
}