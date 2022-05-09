/*
기존에도 벽 없고 다음에도 벽 없다
기존에는 벽 뚫었고 다음에는 벽 없다
기존에는 벽 없고 다음에는 벽이 있다.
*/
#include<iostream>
#include<queue>
#include<vector>
#include<string>
#include<algorithm>

using std::cin;
using std::cout;
using std::vector;
using std::queue;
using std::string;

struct Data {
	int x;
	int y;
	Data(int x, int y) : x(x), y(y) {}
};

vector<int> m1 = { -1,1,0,0 };
vector<int> m2 = { 0,0,-1,1 };

int main() {
	cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	int N, M;
	string str;
	cin >> N >> M;
	vector<vector<int>> map(N, vector<int>(M, 0));
	vector<vector<vector<int>>> result_map(N, vector<vector<int>>(M, vector<int>(2, 1000001))); // Q에 저장하지 말고 result_map을 따로 !
	// [0] - 벽 뚫기 x / [1] - 벽 뚫음
	for (int i = 0; i < N; ++i) {
		cin >> str;
		for (int j = 0; j < M; ++j) {
			map[i][j] = str[j] - '0';
		}
	}

	queue<Data> Q;
	Q.push(Data(0, 0));
	result_map[0][0][0] = 1;
	while (!Q.empty()) {
		Data now = Q.front();
		if (now.x == N - 1 and now.y == M - 1) break;
		Q.pop();
		for (int i = 0; i < 4; ++i) { // up down left right 순서
			if (now.x + m1[i] >= 0 && now.x + m1[i] < N && now.y + m2[i] >= 0 && now.y + m2[i] < M) {
				if (map[now.x + m1[i]][now.y + m2[i]] == 0) { // 벽 x
					if (result_map[now.x][now.y][0] < 1000001 && result_map[now.x+m1[i]][now.y+m2[i]][0] > result_map[now.x][now.y][0] + 1) { // 기존에도 벽 x
						result_map[now.x + m1[i]][now.y + m2[i]][0] = result_map[now.x][now.y][0] + 1;
						Q.push(Data(now.x + m1[i], now.y + m2[i]));
					}
					else if (result_map[now.x][now.y][1] < 1000001 && result_map[now.x + m1[i]][now.y + m2[i]][1] > result_map[now.x][now.y][1] + 1) { // 기존에 이미 벽 통과 된 경우
						result_map[now.x + m1[i]][now.y + m2[i]][1] = result_map[now.x][now.y][1] + 1;
						Q.push(Data(now.x + m1[i], now.y + m2[i]));
					}
				}
				// 기존에는 벽 없었는데 이제 벽이 있다.
				else if (map[now.x + m1[i]][now.y + m2[i]] == 1 && result_map[now.x][now.y][0] < 1000001 && result_map[now.x + m1[i]][now.y + m2[i]][1] > result_map[now.x][now.y][0] + 1) {
					Q.push(Data(now.x + m1[i], now.y + m2[i]));
					result_map[now.x + m1[i]][now.y + m2[i]][1] = result_map[now.x][now.y][0] + 1;
				}
			}
		}
	}
	if (Q.empty()) cout << -1;
	else cout << std::min(result_map[N-1][M-1][0], result_map[N-1][M-1][1]);
	return 0;
}