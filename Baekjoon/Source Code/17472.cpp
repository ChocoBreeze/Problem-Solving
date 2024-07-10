#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>

using namespace std;

int N, M;
vector<int> dx = { -1,1,0,0 };
vector<int> dy = { 0,0,-1,1 };
const int INF = 1000000000;

struct e_t {
	int from;
	int to;
	int weight;
	e_t(int f, int t, int w) : from(f), to(t), weight(w) {}
};

struct Union_Find {
	vector<int> par, siz;
	Union_Find(int n) : par(n, -1), siz(n, 1) {}

	int root(int x) {
		if (par[x] == -1) return x;
		else return par[x] = root(par[x]);
	}
	bool unite(int x, int y) {
		x = root(x), y = root(y);
		if (x == y) return false;
		if (siz[x] < siz[y]) swap(x, y);
		par[y] = x;
		siz[x] += siz[y];
		return true;
	}
};

void make_island(vector<vector<int>>& m, int x, int y, int island_num) {
	queue<pair<int, int>> Q;
	Q.push(make_pair(x,y));
	while (!Q.empty()) {
		pair<int, int> now = Q.front();
		m[now.first][now.second] = island_num;
		Q.pop();
		for (int i = 0; i < 4; ++i) {
			int nx = now.first + dx[i], ny = now.second + dy[i];
			if (nx >= 0 && nx < N && ny >= 0 && ny < M) {
				if (m[nx][ny] == 100) {
					Q.push(make_pair(nx, ny));
				}
			}
		}
	}
}

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	cin >> N >> M;
	vector<vector<int>> m(N, vector<int>(M, 0));
	for (auto& i : m) {
		for (auto& j : i) {
			cin >> j;
			if (j == 1) j = 100;
		}
	}
	int index = 1;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			if (m[i][j] == 100) {
				make_island(m,i,j, index);
				++index;
			}
		}
	}
	auto compare = [](const e_t& a, const e_t& b) {
		return a.weight > b.weight;
	};
	// index의 최종 결과 = 섬의 개수 + 1
	vector<vector<int>> AM(index, vector<int>(index, INF));
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			if (m[i][j] != 0) {
				for (int k = 0; k < 4; ++k) { // 방향
					for (int move = 1;;++move) { // 간 거리
						int nx = i + dx[k] * move, ny = j + dy[k] * move;
						if (!(nx >= 0 && nx < N && ny >= 0 && ny < M)) break;
						if (m[nx][ny]==m[i][j]) break;
						if (m[nx][ny]!=0 && m[nx][ny] != m[i][j]) {
							if (move > 2 && AM[m[i][j]][m[nx][ny]] > move - 1) { // 다리 길이 > 2
								AM[m[i][j]][m[nx][ny]] = move - 1;
								AM[m[nx][ny]][m[i][j]] = move - 1;
							}
							break;
						}
					}
				}
			}
		}
	}
	priority_queue<e_t, vector<e_t>, decltype(compare)> PQ(compare); // min heap

	for (int i = 1; i < index; ++i) {
		for (int j = i + 1; j < index; ++j) {
			if(AM[i][j]!=INF) PQ.push(e_t(i, j, AM[i][j])); // 갈 수 있다면 edge push
		}
	}

	Union_Find uf(index); 
	int edge_count = 0, answer = 0;
	while (!PQ.empty()) {
		e_t now = PQ.top();
		PQ.pop();
		if (uf.root(now.from) == uf.root(now.to)) continue;
		answer += now.weight;
		edge_count++;
		if (edge_count == index - 2) break; // 섬의 개수 - 1 = index - 2
		uf.unite(now.from, now.to);
	}

	if (edge_count == index - 2) cout << answer;
	else cout << -1;

	return 0;
}