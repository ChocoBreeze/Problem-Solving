#include<iostream>
#include<vector>
#include<string>
#include<tuple>
#include<queue>

using std::cin;
using std::cout;
using std::vector;
using std::string;
using std::tuple;
using std::queue;
using std::make_tuple;
using std::get;

int main() {
	cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	int N, M;
	string str;
	cin >> N >> M;
	vector<vector<int>> maps(N, vector<int>(M, 0));
	for (int i = 0; i < N; ++i) {
		cin >> str;
		for (int j = 0; j < M; ++j) {
			maps[i][j] = str[j] - '0';
		}
	}
	std::queue<tuple<int, int, int>> Q; // x, y, cost
	Q.push(make_tuple(0, 0, 1));
	while (!(get<0>(Q.front()) == N - 1 && get<1>(Q.front()) == M - 1)) {
		auto now = Q.front();
		Q.pop();
		int i = get<0>(now), j = get<1>(now), cost = get<2>(now);
		maps[i][j] = 0;
		if (i >= 1 && maps[i - 1][j] == 1) { Q.push(make_tuple(i - 1, j, cost + 1)); maps[i - 1][j] = 0; }
		if (i < N - 1 && maps[i + 1][j] == 1) { Q.push(make_tuple(i + 1, j, cost + 1)); maps[i + 1][j] = 0; }
		if (j >= 1 && maps[i][j - 1] == 1) { Q.push(make_tuple(i, j - 1, cost + 1)); maps[i][j - 1] = 0; }
		if (j < M - 1 && maps[i][j + 1] == 1) { Q.push(make_tuple(i, j + 1, cost + 1)); maps[i][j + 1] = 0;	}
	}
	std::cout << get<2>(Q.front());
	return 0;
}