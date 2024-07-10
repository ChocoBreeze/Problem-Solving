#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

vector<int> dx = { -1,1,0,0 };
vector<int> dy = { 0,0,-1,1 };
int N, M; // 3 <= N, M <= 10

struct coord {
	int x;
	int y;
	coord(int x, int y) : x(x), y(y) {}
};

struct Data {
	coord R;
	coord B;
	Data(coord R, coord B) : R(R), B(B) {}
};

coord B(0, 0), R(0, 0), O(0, 0);

coord move_B(vector<string>& map, int B_x, int B_y, int i) {
	while (map[B_x + dx[i]][B_y + dy[i]] != '#') {
		if (map[B_x][B_y] == 'O') break;
		B_x += dx[i];
		B_y += dy[i];
	}
	coord new_B(B_x, B_y);
	return new_B;
}

coord move_R(vector<string>& map, int R_x, int R_y, int i) {
	while (map[R_x + dx[i]][R_y + dy[i]] != '#') {
		if (map[R_x][R_y] == 'O') break;
		R_x += dx[i];
		R_y += dy[i];
	}
	coord new_R(R_x, R_y);
	return new_R;
}


int bfs(vector<string>& map) {
	int answer = -1;
	vector<vector<vector<vector<int>>>> chk(N, vector<vector<vector<int>>>(M, vector<vector<int>>(N, vector<int>(M, 11))));
	// R[][] B[][] 
	queue<Data> Q; // R, B 위치 갱신 둘다 필요..
	Q.push(Data(R,B));
	chk[R.x][R.y][B.x][B.y] = 0;
	for (int t = 1; t <= 10; ++t) {
		queue<Data> Q_;
		while (!Q.empty()) {
			Data now = Q.front();
			Q.pop();
			coord new_R(0,0), new_B(0,0);
			for (int i = 0; i < 4; ++i) {
				// 가다가 만날 수도 있네..
				int diff_X = now.B.x - now.R.x, diff_Y = now.B.y - now.R.y;
				bool is_meet = false;
				if ((diff_X * dx[i] > 0 && diff_Y == 0 && dy[i] == 0) || (diff_X == 0 && dx[i] == 0 && diff_Y * dy[i] > 0)) {
					is_meet = true;
				}
				// 각 밖에는 #으로 감싸져 있으니 경계 검사 필요 x
				if (is_meet) { // B를 먼저 move
					new_B = move_B(map, now.B.x, now.B.y, i);
					if (map[new_B.x][new_B.y] == 'O') continue;
					new_R = move_R(map, now.R.x, now.R.y, i);
					if (map[new_R.x][new_R.y] == 'O') { // R만 나온 경우
						answer = t;
						break;
					}
					if (new_R.x == new_B.x && new_R.y == new_B.y) {
						new_R.x = new_B.x - dx[i];
						new_R.y = new_B.y - dy[i];
					}
				}
				else { // R를 먼저 move
					new_R = move_R(map, now.R.x, now.R.y, i);
					new_B = move_B(map, now.B.x, now.B.y, i);
					if (map[new_B.x][new_B.y] == 'O') continue;
					if (map[new_R.x][new_R.y] == 'O' && map[new_B.x][new_B.y] == 'O') continue; // 동시에 나온 경우
					if (map[new_R.x][new_R.y] == 'O') { // R만 나온 경우
						answer = t;
						break;
					}
					if (new_R.x == new_B.x && new_R.y == new_B.y) {
						new_B.x = new_R.x - dx[i];
						new_B.y = new_R.y - dy[i];
					}
				}
				if (chk[new_R.x][new_R.y][new_B.x][new_B.y] > t) {
					Q_.push(Data(new_R, new_B));
					chk[new_R.x][new_R.y][new_B.x][new_B.y] = t;
				}
			}
			if (answer != -1) break;
		}
		if (answer != -1) break;
		Q = move(Q_);
	}
	return answer;
}

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	cin >> N >> M;
	vector<string> map(N);
	for (int n = 0; n < N; ++n) {
		cin >> map[n];
		for (int m = 0; m < M; ++m) {
			if (map[n][m] == 'B') {
				B.x = n;
				B.y = m;
				map[n][m] = '.';
			}
			else if (map[n][m] == 'R') {
				R.x = n;
				R.y = m;
				map[n][m] = '.';
			}
			else if (map[n][m] == 'O') {
				O.x = n;
				O.y = m;
			}
		}
	}
	int answer = bfs(map);
	cout << answer;
	return 0;
}