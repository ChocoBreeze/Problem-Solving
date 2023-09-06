// 이분 매칭 공부
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


struct SE {
	int s, e;
	SE(int s, int e) : s(s), e(e) {}
};
vector<SE> graph;
vector<int> visited, A, B;

bool Dfs(int curr) {
	visited[curr] = 1;

	for (int next{ graph[curr].s }; next <= graph[curr].e; ++next) {
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
	int T; cin >> T;
	while (T--) {
		int N, M; cin >> N >> M; // 책이 N권, 학부생이 M명
		graph = vector<SE>(M, SE(0,0)); // 0 ~ N - 1

		for (SE& se : graph) { // 0 ~ M - 1
			cin >> se.s >> se.e;
			se.s--, se.e--;
		}

		int answer{};
		A = vector<int>(M, -1); // 학부생
		B = vector<int>(N, -1); // 책

		for (int m{}; m < M; ++m) {
			// 아직 매칭되지 않은 그룹 A 정점에 대해 매칭 시도
			if (A[m] == -1) {
				vector<int>(M, 0).swap(visited); // visited 배열 초기화
				if (Dfs(m)) ++answer;
			}
		}
		cout << answer << '\n';
	}

	return 0;
}