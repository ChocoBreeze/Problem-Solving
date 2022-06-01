#include<algorithm>
#include<vector>
#include<iostream>
#include<queue>
using std::vector;
using std::cin;
using std::cout;
using std::queue;

struct coordinate {
	int x;
	int y;
	int z;
	coordinate(int x, int y, int z) : x(x), y(y), z(z) {}
};

vector<int> m1 = {-1, 1, 0, 0, 0, 0}; // H
vector<int> m2 = {0, 0, -1, 1, 0, 0}; // N
vector<int> m3 = {0, 0, 0, 0, -1, 1}; // M

int main() {
	cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	int N, M, H, cnt_ones = 0 , cnt_zeros = 0;
	cin >> M >> N >> H;
	vector<vector<vector<int>>> tomatoes(H, vector<vector<int>>(N, vector<int>(M,0)));
	queue<coordinate> Q;
	for (int i = 0; i < H; ++i) {
		for (int j = 0; j < N; ++j) {
			for (int k = 0; k < M; ++k) {
				cin >> tomatoes[i][j][k];
				if (tomatoes[i][j][k] == 0) ++cnt_zeros;
				else if (tomatoes[i][j][k] == 1) {
					++cnt_ones;
					Q.push(coordinate(i, j, k));
				}
			}
		}
	}
	int goals = cnt_zeros + cnt_ones;
	if (goals == cnt_ones) std::cout << 0;
	else {
		for (int answer = 1;; ++answer) {
			queue<coordinate> Q_tmp;
			int cnt_ones_tmp = cnt_ones;
			while (!Q.empty()) {
				auto now = Q.front();
				Q.pop();
				for (int i = 0; i < 6; ++i) {
					if (now.x + m1[i] >= 0 && now.x + m1[i] < H && now.y + m2[i] >= 0 && now.y + m2[i] < N && now.z + m3[i] >= 0 && now.z + m3[i] < M) { // 좌표 확인
						if (tomatoes[now.x + m1[i]][now.y + m2[i]][now.z + m3[i]] == 0) {
							Q_tmp.push(coordinate(now.x + m1[i], now.y + m2[i], now.z + m3[i]));
							tomatoes[now.x + m1[i]][now.y + m2[i]][now.z + m3[i]] = 1; // 중복 삽입 방지
							++cnt_ones;
						}
					}
				}
				if (cnt_ones == goals) break;
			}
			if (cnt_ones == goals) {
				std::cout << answer;
				break;
			}
			if (cnt_ones_tmp == cnt_ones) {
				std::cout << -1;
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