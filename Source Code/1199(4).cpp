// 양방향 그래프(무향 그래프) -> 오일러 회로 - 차수가 홀수인 정점이 0개일 때 존재함.
// 접근 참고 : https://m.blog.naver.com/kks227/220800097205
// https://www.acmicpc.net/source/65454028
// 아이디어 : 정점마다 next 시작점을 기억해두자..(처음부터 순회하지 말고)

// line 96 확인

#include <iostream>
#include <vector>

using namespace std;

// 두 정점 사이에 간선이 여러 개 있을 수 있다
struct Edge {
	int to, cnt, rev; // 간선이 향하는 정점, 간선 개수, 반대방향 간선 인덱스
	Edge(int to, int cnt, int rev) : to(to), cnt(cnt), rev(rev) {}
};

vector<vector<Edge>> graph;
vector<int> degree, visited; // 정점의 차수, 방문 여부
vector<int> nextStart;

// 컴포넌트 별로 방문하는 dfs
int dfs(int curr) {
	int ret = 1;
	visited[curr] = 1;
	for (auto& [to, cnt, rev] : graph[curr]) {
		if (!visited[to]) ret += dfs(to);
	}
	return ret;
}

// 오일러 회로 출력용 dfs
void Eulerian(int curr) {
	int currSize = static_cast<int>(graph[curr].size());
	while (nextStart[curr] < currSize) {
		while (nextStart[curr] < currSize && graph[curr][nextStart[curr]].cnt == 0) nextStart[curr]++;
		// nextStart[curr] == currSize일 수도 있으니까
		if (nextStart[curr] < currSize) {
			auto& [to, cnt, rev] = graph[curr][nextStart[curr]];
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
	visited = vector<int>(N, 0);
	nextStart = vector<int>(N, 0);

	for (int i{}; i < N; ++i) {
		for (int j{}; j < N; ++j) {
			int cnt{}; cin >> cnt; // 간선 개수
			// 대칭인 그래프(j>i)인 경우에만 처리(no self-loop)
			if (j > i && cnt) {
				int iRev = static_cast<int>(graph[i].size());
				int jRev = static_cast<int>(graph[j].size());
				graph[i].emplace_back(j, cnt, jRev);
				graph[j].emplace_back(i, cnt, iRev);
				degree[i] += cnt, degree[j] += cnt; // 각 정점의 차수 증가
			}
		}
	}

	// 1. 오일러 회로 존재 여부 확인 - 차수가 홀수인 정점이 하나라도 있으면 안 됨
	for (int& d : degree) {
		if (d & 1) {
			cout << "-1\n";
			return 0;
		}
	}

	// 오일러 회로 존재함. => 계산(DFS)
	// 이 경우엔 시작점이 어떤 정점이어도 오일러 회로 구하는 것이 가능함.
	// 생각보다 이 코드는 그렇게 큰 차이 안 나더라..
	bool flag{};
	int start = -1;
	for (int n{}; n < N; ++n) {
		if (!visited[n]) {
			int cSize = dfs(n);
			if (cSize > 1) {
				if (flag) {
					// 크기가 2 이상인 컴포넌트가 2개 이상이면 불가능
					// 서로 연결되지 않은 크기 2 이상인 컴포넌트 => 오일러 회로 만들 수 없음.
					// 크기 1개짜리 정점 하나 있는 것은 가능
					cout << "-1\n";
					return 0;
				}
				else {
					// start = n; // 이거는 왜 필요한거지?
					flag = true;
				}
			}
		}
	}

	if (start == -1) start = 0;

	// 오일러 회로 찾기 시작
	Eulerian(start);

	return 0;
}