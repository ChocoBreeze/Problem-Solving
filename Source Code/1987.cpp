#include<iostream>
#include<algorithm>
#include<vector>
#include<string>

using namespace std;

vector<int> dx = { -1,1,0,0 };
vector<int> dy = { 0,0,-1,1 };
int R, C;

int dfs(vector<string>& m, vector<bool>& chk,int x,int y) {
	int answer = 1;
	chk[m[x][y] - 'A'] = true;
	for (int i = 0; i < 4; ++i) {
		if (x + dx[i] >= 0 && x + dx[i] < R && y + dy[i] >= 0 && y + dy[i] < C) {
			if (!chk[m[x + dx[i]][y + dy[i]] - 'A']) {
				chk[m[x + dx[i]][y + dy[i]] - 'A'] = true;
				answer = max(answer, 1 + dfs(m, chk, x + dx[i], y + dy[i]));
				chk[m[x + dx[i]][y + dy[i]] - 'A'] = false;
			}
		}
	}
	return answer;
}

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	cin >> R >> C;
	vector<string> m(R);
	for (auto & i : m) {
		cin >> i;
	}
	int x = 0, y = 0;
	vector<bool> chk(26, false);
	cout << dfs(m,chk,x,y);
	return 0;
}