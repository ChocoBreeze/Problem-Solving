#include<iostream>
#include<vector>
#include<queue>
using std::vector;
using std::queue;
int bfs(vector<bool>&chk, vector<vector<int>>& Graph ) {
	int cnt = 0;
	queue<int> q;
	q.push(1);
	chk[1] = true;
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		++cnt;
		for (auto& i : Graph[v]) {
			if (chk[i]) continue;
			q.push(i);
			chk[i] = true;
		}
	}
	return cnt;
}

int main() {
	std::cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	int N, M, a, b;
	std::cin >> N >> M;
	vector<bool> chk(N+1, false);
	vector<vector<int>> Graph(N+1);
	for (int i = 0; i < M; ++i) {
		std::cin >> a >> b;
		Graph[a].push_back(b);
		Graph[b].push_back(a);
	}
	std::cout << bfs(chk, Graph) - 1; // 1은 제외
	return 0;
}