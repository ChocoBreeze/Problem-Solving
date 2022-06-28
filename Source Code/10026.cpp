#include<iostream>
#include<vector>
#include<string>
#include<queue>
#include<utility>

using namespace std;

vector<int> dx = { -1, 1, 0, 0 };
vector<int> dy = { 0, 0, -1, 1 };
int N;

void bfs(vector<string>& m,int x,int y, char color) {
	queue<pair<int,int>> Q;
	Q.push(make_pair(x, y));
	while (!Q.empty()) {
		pair<int, int> now = Q.front();
		Q.pop();
		for (int i = 0; i < 4; ++i) {
			if (now.first + dx[i] >= 0 && now.first + dx[i] < N && now.second + dy[i] >= 0 && now.second + dy[i] < N) {
				if (m[now.first + dx[i]][now.second + dy[i]] == color) {
					m[now.first + dx[i]][now.second + dy[i]] = 'C'; // clear
					Q.push(make_pair(now.first + dx[i], now.second + dy[i]));
				}
			}
		}
	}
}

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	cin >> N;
	vector<string> m1(N,""), m2(N,"");
	for (int i = 0; i < N; ++i) {
		cin >> m1[i];
		m2[i] = m1[i];
		for (int j = 0; j < N; ++j) {
			if (m2[i][j] == 'R') m2[i][j] = 'G';
		}
	}
	int cnt1 = 0, cnt2 = 0;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			if (m1[i][j] != 'C') {
				cnt1++;
				bfs(m1, i, j, m1[i][j]);
			}
			if (m2[i][j] != 'C') {
				cnt2++;
				bfs(m2, i, j, m2[i][j]);
			}
		}
	}
	cout << cnt1 << " " << cnt2;
	return 0;
}