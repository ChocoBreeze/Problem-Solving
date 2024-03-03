/*
< Hopcroft-Karp : O(E * sqrt(V)) >
참고 : https://m.blog.naver.com/kks227/220816033373
참고 : https://blog.naver.com/jinhan814/222284335708
1. alternating path: 
그래프 위의 경로인데, 어떤 매칭 M에 대해 매칭에 속한 간선 - 속하지 않은 간선 - 속한 간선 - 속하지 않은 간선 - ... - 속한 간선 순으로 번갈아가며 속하는 규칙이 반복되는 경로
2. augmenting path:
양 끝점은 매칭에 속하지 않고, 나머지 경로가 교차 경로를 이루는 경로 
=> 증가 경로가 존재한다면 반드시 매칭 크기를 1 늘릴 수 있다.
==> 증가 경로 발견 시 => 안 속함 - 속함 - 안 속함 - 속함 ... - 속함 - 안 속함 상태
==> 반드시 레벨이 1 증가하는 순으로만 정점들을 거쳐야 함.
==> 이를 뒤집으면 새로운 매칭을 발견할 수 있다!(기존 매칭에 비해 크기 1증가)
*/
// 2156KB, 0ms

#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;
constinit const int INF = 1 << 30;

int N, M;
vector<bool> used; // (A 그룹의) 이 정점이 매칭에 속해 있는가?
vector<vector<int>> adj; // 간선 정보 저장
vector<int> A, B, level;
// A[i], B[i]: 그룹의 i번 정점과 매칭된 상대편 그룹 정점 번호
// level : 레벨 그래프에서 정점의 레벨(SRC가 0)

// 호프크로프트 카프 전용 bfs 함수 : A 그룹의 각 정점에 레벨을 매김
void bfs() {
	queue<int> q;
	// 매칭에 안 속한 A 그룹의 정점만 레벨 0인 채로 시작
	for (int i{}; i < N; ++i) {
		if (!used[i]) {
			level[i] = 0;
			q.push(i);
		}
		else level[i] = INF;
	}

	// BFS를 통해 A그룹 정점에 0, 1, 2, 3, ... 의 레벨을 매김
	while (!q.empty()) {
		int a = q.front(); q.pop();
		for (int& b : adj[a]) {
			if (B[b] != -1 && level[B[b]] == INF) {
				level[B[b]] = level[a] + 1;
				q.push(B[b]);
			}
		}
	}
}

// 호프크로프트 카프 전용 dfs 함수 : 새 매칭을 찾으면 true
bool dfs(int a) {
	for (int& b : adj[a]) {
		// 이분 매칭 코드와 상당히 유사하나, level 배열에 대한 조건이 추가로 붙음
		if (B[b] == -1 || (level[B[b]] == level[a] + 1 && dfs(B[b]))) {
			// used 배열 값도 true가 됨
			used[a] = true;
			A[a] = b;
			B[b] = a;
			return true;
		}
	}
	return false;
}

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	cin >> N >> M; // 소의 수, 축사의 수
	adj = vector(N, vector<int>());
	level = vector(N, 0);
	used = vector(N, false);
	
	for (int n{}; n < N; ++n) {
		int S{}; cin >> S; // 들어가길 원하는 축사 수
		for (int i{}; i < S; ++i) {
			int s{}; cin >> s; --s; 
			adj[n].push_back(s);
		}
	}

	// Hopcroft-Karp
	int match{};
	A = vector(N, -1);
	B = vector(M, -1);

	while (1) {
		// 각 정점에 레벨을 매기고 시작
		bfs();

		// 이분 매칭과 비슷하게 A그룹 정점을 순회하며 매칭 증가량 찾기
		int flow{};
		for (int n{}; n < N; ++n) {
			if (!used[n] && dfs(n)) ++flow;
		}

		// 더 이상 증가 경로를 못 찾으면 알고리즘 종료
		if (flow == 0) break;

		// 찾았을 경우 반복
		match += flow;
	}
	cout << match << '\n'; // 결과 출력
	
	return 0;
}