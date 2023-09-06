// https://m.blog.naver.com/kks227/220807541506
// 이분 매칭 공부
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> graph;
vector<int> visited, A, B;

bool Dfs(int curr) {
	visited[curr] = 1;

	for (int& next : graph[curr]) {
		// 반대편이 매칭되지 않거나 (B[next] == -1)
		// 매칭되어 있었지만 원래 매칭되어 있던 정점을 다른 정점과 매칭시킬 수 있으면 성공
		if (B[next] == -1 || (!visited[B[next]] && Dfs(B[next]))) {
			A[curr] = next;
			B[next] = curr;
			return true;
		}
	}
	// 매칭 실패
	return false;
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	int N, M; cin >> N >> M;

	graph = vector<vector<int>>(N); // 0 ~ N - 1 (소 -> 축사)
	for (int n{}; n < N; ++n) { 
		int S; cin >> S;
		for (int s{}; s < S; ++s) {
			int k; cin >> k;
			graph[n].push_back(k - 1);
		}
	}

	int answer{};
	A = vector<int>(N, -1); // 소
	B = vector<int>(M, -1); // 축사 (N으로 잡으면 out of bounds)

	for (int n{}; n < N; ++n) {
		// 아직 매칭되지 않은 그룹 A 정점에 대해 매칭 시도
		if (A[n] == -1) {
			vector<int>(N, 0).swap(visited); // visited 배열 초기화
			if (Dfs(n)) ++answer;
		}
	}
	cout << answer << '\n';

	return 0;
}