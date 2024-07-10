// Bipartite Matching
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> graph;
vector<int> A, B, visited;

bool DFS(int curr) {
	visited[curr] = 1;

	for (int& next : graph[curr]) {
		// 연결이 되어 있지 않거나 
		// 매칭되어 있던 점을 다른 정점과 매칭시킬 수 있으면
		if (B[next] == 0 || (!visited[B[next]] && DFS(B[next]))) { // DFS(next) 아님!
			A[curr] = next;
			B[next] = curr;
			return true;
		}
	}
	return false;
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	int N, M; cin >> N >> M; // 직원 1 ~ N, 일 1 ~ M
	// 각 직원은 최대 두 개의 일을 할 수 있고 => 직원 정점을 2개 만들자
	const int WORKERNUM = (N << 1) + 1;
	// 1 -> 1, 2
	// n -> 2n - 1, 2n

	graph = vector<vector<int>>(WORKERNUM);
	for (int n{ 1 }; n <= N; ++n) {
		int cnt{}; cin >> cnt;
		for (int i{}; i < cnt; ++i) {
			int work{}; cin >> work;
			int first{ (n << 1) - 1 }, second{ n << 1 };
			graph[first].push_back(work);
			graph[second].push_back(work);
		}
	}

	int match{};
	A = vector<int>(WORKERNUM, 0);
	B = vector<int>(M + 1, 0);
	for (int n{ 1 }; n < WORKERNUM; ++n) {
		if (!A[n]) {
			visited.assign(WORKERNUM, 0);
			if (DFS(n)) ++match;
		}
	}

	cout << match << '\n';

	return 0;
}