#include<iostream>
#include<vector>
#include<queue>
#include<string>
#include<algorithm>

using std::vector;
using std::queue;
using std::cin;
using std::cout;
using std::string;
using std::pair;
using std::make_pair;
using std::sort;

int bfs(vector<vector<int>>& map,int p,int q) {
	int cnt = 1;
	queue<pair<int , int>> Q;
	Q.push(make_pair(p, q));
	map[p][q] = 0;
	while (!Q.empty()) {
		auto v = Q.front();
		p = v.first;
		q = v.second;
		Q.pop();
		// 상하좌우
		if (p >= 1 && map[p - 1][q] == 1) { // up
			Q.push(make_pair(p - 1, q)); 
			map[p - 1][q] = 0;
			++cnt;
		}
		if (p + 1 < map.size() && map[p + 1][q] == 1) { // down
			Q.push(make_pair(p + 1, q));
			map[p + 1][q] = 0;
			++cnt;
		}
		if (q >= 1 && map[p][q - 1] == 1) { // left
			Q.push(make_pair(p, q - 1)); 
			map[p][q - 1] = 0;
			++cnt;
		}
		if (q + 1 < map.size() && map[p][q + 1] == 1) { // right
			Q.push(make_pair(p, q + 1)); 
			map[p][q + 1] = 0;
			++cnt;
		}
	}
	return cnt;
}

int main() {
	cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	int N;
	string str;
	cin >> N;
	vector<vector<int>> map(N, vector<int>(N, 0));
	vector<int> result;
	for (int i = 0; i < N; ++i) {
		cin >> str;
		for (int j = 0; j < N; ++j) {
			map[i][j] = str[j] - '0';
		}
	}
	
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			if (map[i][j] == 1) {
				result.push_back(bfs(map, i, j));
			}
		}
	}
	sort(result.begin(),result.end());
	std::cout << result.size() << "\n";
	for (auto& i : result) {
		cout << i << "\n";
	}
	return 0;
}