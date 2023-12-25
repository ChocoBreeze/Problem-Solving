/*
* general case there are n jobs numbered from 0 to n-1, n servers numbered from n to 2 *n-1
* The problem asks to find the maximum number of jobs that can be processed
*/

// https://m.blog.naver.com/kks227/220816033373
// Hopcroft-Karp 공부

#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;
constinit const int INF = 1'000'000'000;

int N;
vector<int> A, B, dist;
// dist[i]: (A그룹의) i번 정점의 레벨(?)
// A[i], B[i]: 그룹의 i번 정점과 매칭된 상대편 그룹 정점 번호
vector<bool> used; // (A 그룹의) 이 정점이 매칭에 속해 있는가?
vector<vector<int>> adj;

// 호프크로프트 카프 전용 bfs 함수 : A 그룹의 각 정점에 레벨을 매김
void bfs() {
	queue<int> Q;
	// 매칭에 안 속한 A 그룹의 정점만 레벨 0인 채로 시작
	for (int i{}; i < N; ++i) {
		if (!used[i]) {
			dist[i] = 0;
			Q.push(i);
		}
		else dist[i] = INF;
	}

	// BFS를 통해 A그룹 정점에 0, 1, 2, 3, ... 의 레벨을 매김
	while (!Q.empty()) {
		int now = Q.front(); Q.pop();
		for (int& next : adj[now]) {
			if (B[next] != -1 && dist[B[next]] == INF) {
				dist[B[next]] = dist[now] + 1;
				Q.push(B[next]);
			}
		}
	}
}

// 호프크로프트 카프 전용 dfs 함수 : 새 매칭을 찾으면 true
bool dfs(int a) {
	for (int& b : adj[a]) {
		// 이분 매칭 코드와 상당히 유사하나, dist 배열에 대한 조건이 추가로 붙음
		if (B[b] == -1 || (dist[B[b]] == dist[a] + 1 && dfs(B[b]))) {
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
	while (cin >> N) {
		A = vector<int>(N, -1);
		B = vector<int>(N, -1);
		used = vector<bool>(N, false);
		adj = vector<vector<int>>(N);
		dist = vector<int>(N, 0);

		// input
		for (int n{}; n < N; ++n) { // 그래프 정보 입력 받기
			int job, serverN;
			char colon, openBracket, closeBracket;
			cin >> job >> colon >> openBracket >> serverN >> closeBracket; // job: (serverN)
			for (int s{}; s < serverN; ++s) {
				int server{}; cin >> server;
				adj[job].push_back(server - N);
			}
		}

		// Hopcroft-Karp
		int match{};

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
	}
	return 0;
}