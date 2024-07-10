// 양방향 그래프(무향 그래프) -> 오일러 회로 - 차수가 홀수인 정점이 0개일 때 존재함.
// 접근 참고 : https://m.blog.naver.com/kks227/220800097205
// https://justicehui.github.io/hard-algorithm/2019/01/04/euler/
// https://www.acmicpc.net/source/65454028
// 아이디어 : 정점마다 next 시작점을 기억해두자..(처음부터 순회하지 말고)

#include <iostream>
#include <vector>

using namespace std;

// adjacency matrix

vector<vector<int>> graph;
vector<int> nextStart;
int N{};

// 오일러 회로 출력용 dfs
void Eulerian(int curr) {
	while (nextStart[curr] < N) {
		while (nextStart[curr] < N && graph[curr][nextStart[curr]] == 0) nextStart[curr]++;
		if (nextStart[curr] < N) {
			int& next = nextStart[curr];
			if (graph[curr][next]) {
				--graph[curr][next];
				--graph[next][curr];
				Eulerian(next);
			}
		}
	}
	cout << curr + 1 << ' ';
}

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	cin >> N;

	graph = vector<vector<int>>(N, vector<int>(N, 0)); // 0 ~ N - 1
	nextStart = vector<int>(N, 0);

	for (int i{}; i < N; ++i) {
		int degree{};
		for (int j{}; j < N; ++j) {
			int cnt{}; cin >> cnt; // 간선 개수
			graph[i][j] = cnt;
			degree += cnt;
		}
		if (degree & 1) {
			// 오일러 회로 존재 여부 확인 - 차수가 홀수인 정점이 하나라도 있으면 안 됨
			cout << "-1\n";
			return 0;
		}
	}

	// 오일러 회로 존재함. => 계산(DFS)
	// 이 경우엔 시작점이 어떤 정점이어도 오일러 회로 구하는 것이 가능함.
	// 또, 입력으로 주어지는 그래프는 모두 연결되어 있다. (컴포넌트 검사 생략)

	// 오일러 회로
	Eulerian(0);

	return 0;
}