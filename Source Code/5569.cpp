// 나눌 생각을 못 했음.
// 남북 - w, 동서 - h
// (1,1) -> (w,h)
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct State {
	int change_north;
	int change_east;
	int nochange_north;
	int nochange_east;
	State(int a, int b, int c, int d) : change_north(a), change_east(b), nochange_north(c), nochange_east(d) {}
};

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	int w, h;
	cin >> w >> h;
	// 4가지 케이스로 나누어서 생각
	// 1. 방향 변경 o, 북쪽으로 옴 = 1 + 3
	// 2. 방향 변경 o, 동쪽으로 옴 = 2 + 4
	// 3. 방향 변경 x, 북쪽으로 옴 = 2
	// 4. 방향 변경 x, 동쪽으로 옴 = 1
	vector<vector<State>> map(w + 1, vector<State>(h + 1, State(0,0,0,0)));
	for (int i = 2; i <= w; ++i) {
		map[i][1].change_east = 1;
	}
	for (int i = 2; i <= h; ++i) {
		map[1][i].change_north = 1;
	}
	for (int i = 2; i <= w; ++i) {
		for (int j = 2; j <= h; ++j) {
			// map[i][j] = map[i - 1][j] + map[i][j - 1];
			map[i][j].change_north = (map[i][j - 1].change_north + map[i][j - 1].nochange_north)%100000;
			map[i][j].change_east = (map[i - 1][j].change_east + map[i - 1][j].nochange_east)%100000;
			map[i][j].nochange_north = map[i][j - 1].change_east%100000;
			map[i][j].nochange_east = map[i - 1][j].change_north%100000;
		}
	}
	cout << (map[w][h].change_east + map[w][h].change_north + map[w][h].nochange_east + map[w][h].nochange_north)%100000;
	return 0;
}