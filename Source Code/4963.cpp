#include<iostream>
#include<vector>
#include<queue>

using namespace std;

vector<int> dx = { -1,-1,-1,0,0,1,1,1 };
vector<int> dy = { -1,0,1,-1,1,-1,0,1 };

struct coord {
	int x;
	int y;
	coord(int x, int y) : x(x), y(y) {}
};

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	int w, h;
	while (1) {
		cin >> w >> h;
		if (w == 0 && h == 0) break;
		vector<vector<int>> m(h, vector<int>(w, 0)); // h, w 잘 보기..
		queue<coord> Q;
		for (int i = 0; i < h;++i) {
			for (int j = 0; j < w;++j) {
				cin >> m[i][j];
				if (m[i][j] == 1) Q.push(coord(i, j)); // 1이 땅, 0이 육지
			}
		}
		int cnt = 0;
		while (!Q.empty()) {
			coord now = Q.front();
			Q.pop();
			if (m[now.x][now.y] == 2) continue;
			++cnt;
			queue<coord> Q_;
			Q_.push(coord(now.x, now.y));
			while (!Q_.empty()) {
				coord now_ = Q_.front();
				Q_.pop();
				for (int i = 0; i < 8; ++i) {
					if (now_.x + dx[i] >= 0 && now_.x + dx[i] < h && now_.y + dy[i] >= 0 && now_.y + dy[i] < w) {
						if (m[now_.x + dx[i]][now_.y + dy[i]] == 1) {
							m[now_.x + dx[i]][now_.y + dy[i]] = 2;
							Q_.push(coord(now_.x + dx[i], now_.y + dy[i]));
						}
					}
				}
			}
		}
		cout << cnt << "\n";
	}
	return 0;
}