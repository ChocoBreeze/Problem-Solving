// 상어 간에 간선 잘 만들기. 
// - 다 같은 경우에 주의하자!
// - 최대 2마리 먹을 수 있는 것도 포인트.
// 2160KB, 0ms
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;
constinit const int INF = 1 << 30;

struct Shark {
	int siz, speed, iq;
	Shark(int siz, int speed, int iq) : siz(siz), speed(speed), iq(iq) {}
};

int N;
vector<bool> used;
vector<vector<int>> adj;
vector<int> A, B, level;

void bfs() {
	queue<int> q;
	// 매칭에 안 속한 A 그룹의 정점만 레벨 0인 채로 시작
	for (int n{}; n < N; ++n) {
		if (!used[n]) {
			level[n] = 0;
			q.push(n);
		}
		else level[n] = INF;
	}

	// A 그룹의 정점에 0, 1, 2, 3, ... 의 레벨을 매김
	while (!q.empty()) {
		int a{ q.front() }; q.pop();
		for (int& b : adj[a]) {
			if (B[b] != -1 && level[B[b]] == INF) {
				level[B[b]] = level[a] + 1;
				q.push(B[b]);
			}
		}
	}
}

bool dfs(int a) {
	for (int& b : adj[a]) {
		if (B[b] == -1 || (level[B[b]] == level[a] + 1 && dfs(B[b]))) { 
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
	cin >> N; // 상어의 수
	vector<Shark> sharks(N, Shark(0, 0, 0));
	for (int n{}; n < N; ++n) {
		Shark& s = sharks[n];
		cin >> s.siz >> s.speed >> s.iq;
	}

	N <<= 1;
	adj = vector(N, vector<int>());
	level = vector(N, 0);
	used = vector(N, false);
	N >>= 1;
	for (int n{}; n < N; ++n) {
		auto& [s1Siz, s1Speed, s1Iq] = sharks[n];
		for (int m{ n + 1 }; m < N; ++m) {
			auto& [s2Siz, s2Speed, s2Iq] = sharks[m];
			if (s1Siz == s2Siz && s1Speed == s2Speed && s1Iq == s2Iq) { // 더 빠른 인덱스인 친구에 추가
				adj[n * 2].push_back(m);
				adj[n * 2 + 1].push_back(m);
			}
			else if (s1Siz >= s2Siz && s1Speed >= s2Speed && s1Iq >= s2Iq) {
				adj[n * 2].push_back(m);
				adj[n * 2 + 1].push_back(m);
			}
			else if (s1Siz <= s2Siz && s1Speed <= s2Speed && s1Iq <= s2Iq) {
				adj[m * 2].push_back(n);
				adj[m * 2 + 1].push_back(n);
			}
		}
	}

	int match{};
	B = vector(N, -1); // 기존 상어 크기
	N <<= 1;
	A = vector(N, -1); // 2배한 상어 크기(정점들을 2배로 늘린 상태)

	while (1) {
		bfs(); // level graph

		int flow{};
		for (int n{}; n < N; ++n) {
			if (!used[n] && dfs(n)) ++flow;
		}

		if (flow == 0) break; // not find augmenting path

		match += flow;
	}
	N >>= 1; // 원래 N
	cout << N - match << '\n'; // N - match 개수 = 남은 상어

	return 0;
}