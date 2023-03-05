// 최단거리 구해서 젤 긴거 하나 빼면 끝?..

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int max_dist;
int dist;
int S, E;

struct edge {
	int to;
	int weight;
};

vector<edge> graph[100001];
int visited[100001]{};
bool find_path = false;

void dfs(int now, int dist) {
	if (now == E) {
		find_path = true;
		cout << dist - max_dist << endl;
		return;
	}
	for (auto& next : graph[now]) {
		if (!visited[next.to]) {
			int temp = max_dist;
			max_dist = max(max_dist, next.weight);
			visited[next.to] = 1;
			dfs(next.to, dist + next.weight);
			if (find_path) return;
			max_dist = temp;
			visited[next.to] = 0;
		}
	}
}

int main() {
	int N;
    cin.tie(NULL)->sync_with_stdio(false);
	cin >> N >> S >> E;
	for (int i = 0; i < N - 1; ++i) {
		int f, t, w;
		cin >> f >> t >> w;
		graph[f].push_back({ t, w });
		graph[t].push_back({ f,w });
	}

	visited[S] = 1; // 빼먹었네?
	dfs(S, 0);

	return 0;
}