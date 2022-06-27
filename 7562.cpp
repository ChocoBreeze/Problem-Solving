#include<iostream>
#include<queue>
#include<vector>

using std::cout;
using std::cin;
using std::vector;
using std::queue;

vector<int> dx = {-1,-2,-2,-1,1,2,2,1};
vector<int> dy = {-2,-1,1,2,2,1,-1,-2};

struct coord {
	int x;
	int y;
	coord(int x, int y) : x(x), y(y) {}
};

int main() {
	cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	int T, I;
	int startx, starty, endx, endy;
	cin >> T;
	for (int i = 0; i < T; ++i) { // Test case
		cin >> I; // chessboard 길이
		vector<vector<int>> chessboard(I, vector<int>(I, -1));
		queue<coord> Q;
		int cnt = 0;
		cin >> startx >> starty;
		chessboard[startx][starty] = cnt++;
		cin >> endx >> endy;
		Q.push(coord(startx, starty));
		for (;; ++cnt) {
			queue<coord> Q_tmp;
			while (!Q.empty()) {
				coord now = Q.front();
				Q.pop();
				for (int i = 0; i < 8; ++i) {
					if (now.x + dx[i] >= 0 && now.y + dy[i] >= 0 && now.x + dx[i] < I && now.y + dy[i] < I) {
						if (chessboard[now.x + dx[i]][now.y + dy[i]] == -1) {
							chessboard[now.x + dx[i]][now.y + dy[i]] = cnt;
							Q_tmp.push(coord(now.x + dx[i], now.y + dy[i]));
						}
					}
				}
				if (chessboard[endx][endy] != -1) break;
			}
			if (chessboard[endx][endy] != -1) {
				std::cout << chessboard[endx][endy] << "\n";
				break;
			}
			while (!Q_tmp.empty()) {
				Q.push(Q_tmp.front());
				Q_tmp.pop();
			}
		}
	}
	return 0;
}