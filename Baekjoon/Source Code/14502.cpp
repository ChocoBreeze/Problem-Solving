#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;

vector<int> dx = { -1,1,0,0 };
vector<int> dy = { 0,0,-1,1 };

struct coord {
	int x;
	int y;
	coord(int x, int y) : x(x), y(y) {}
};

int N, M;

int count_virus(vector<vector<int>>& m, vector<coord>& possible_ones, vector<coord>& virus, int p, int q, int r) {
	vector<vector<int>> m_ = m; // 복사 되나?
	m_[possible_ones[p].x][possible_ones[p].y] = 1;
	m_[possible_ones[q].x][possible_ones[q].y] = 1;
	m_[possible_ones[r].x][possible_ones[r].y] = 1;
	queue<coord> Q;
	for (auto& i : virus) {
		Q.push(i);
	}
	while (!Q.empty()) {
		coord now = Q.front();
		Q.pop();
		for (int i = 0; i < 4; ++i) {
			if (now.x + dx[i] >= 0 && now.x + dx[i] < N && now.y + dy[i] >= 0 && now.y + dy[i] < M) {
				if (m_[now.x + dx[i]][now.y + dy[i]] == 0) {
					m_[now.x + dx[i]][now.y + dy[i]] = 2;
					Q.push(coord(now.x + dx[i], now.y + dy[i]));
				}
			}
		}
	}
	int count = 0;
	for (auto& i : m_) {
		for (auto& j : i) {
			if (j == 0) ++count;
		}
	}
	return count;
}

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	cin >> N >> M;
	vector<vector<int>> m(N, vector<int>(M, 0));
	vector<coord> possible_ones;
	vector<coord> virus;
	for (int i = 0; i < N;++i) {
		for (int j = 0; j < M;++j) {
			cin >> m[i][j];
			if (m[i][j] == 0) possible_ones.push_back(coord(i, j));
			else if (m[i][j] == 2) virus.push_back(coord(i, j));
		}
	}
	int answer = -1;
	for (int p = 0; p < size(possible_ones); ++p) {
		for (int q = p + 1; q < size(possible_ones); ++q) {
			for (int r = q + 1; r < size(possible_ones); ++r) {
				answer = max(answer, count_virus(m, possible_ones, virus, p, q, r));
			}
		}
	}
	cout << answer;
	return 0;
}