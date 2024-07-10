// 양방향 그래프(무향 그래프) -> 오일러 회로 - 차수가 홀수인 정점이 0개일 때 존재함.
// 접근 참고 : https://m.blog.naver.com/kks227/220800097205

#include <iostream>
#include <vector>

using namespace std;

// 두 정점 사이에 간선이 여러 개 있을 수 있다
struct Edge {
	int to, cnt, rev; // 간선이 향하는 정점, 간선 개수, 반대방향 간선 인덱스
	Edge(int to, int cnt, int rev) : to(to), cnt(cnt), rev(rev) {}
};

vector<vector<Edge>> graph;
vector<int> degree; // 정점의 차수

// 오일러 회로 출력용 dfs
void Eulerian(int curr) {
	for (auto& [to, cnt, rev] : graph[curr]) {
		if (cnt > 0) {
			// 순방향, 역방향 간선 하나씩 지우기
			--cnt;
			--graph[to][rev].cnt;
			Eulerian(to); // dfs
		}
	}
	cout << curr + 1 << ' ';
}

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int N{}; cin >> N;

	graph = vector<vector<Edge>>(N); // 0 ~ N - 1
	degree = vector<int>(N, 0);

	for (int i{}; i < N; ++i) {
		for (int j{}; j < N; ++j) {
			int cnt{}; cin >> cnt; // 간선 개수
			// 대칭인 그래프(j>i)인 경우에만 처리(no self-loop)
			if (j > i && cnt) {
				int iRev = static_cast<int>(graph[i].size());
				int jRev = static_cast<int>(graph[j].size());
				graph[i].emplace_back(j, cnt, jRev);
				graph[j].emplace_back(i, cnt, iRev);
				degree[i]+=cnt, degree[j]+=cnt; // 각 정점의 차수 증가
			}
		}
		if (degree[i] & 1) {
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