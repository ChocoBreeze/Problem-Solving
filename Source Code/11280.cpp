// https://m.blog.naver.com/kks227/220803009418
// 공부
// 음수 정점 처리
// SCC - 또 짜려니까 까먹었따..

#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

vector<vector<int>> graph;

vector<int> finished; // SCC 구성 완료

vector<int> orders; // 방문 순서
int order{};

vector<int> SCCnums; // SCCnums[i] : i가 속한 SCC 번호
int SCCcnts{};

stack<int> S;

int DFS(int curr) {
	int result = orders[curr] = ++order;
	S.push(curr);

	for (int& next : graph[curr]) {
		if (orders[next] == 0) result = min(result, DFS(next)); // 방문을 안 한
		else if (!finished[next]) result = min(result, orders[next]); // 아직 SCC 구성이 안 끝난
	}

	if (result == orders[curr]) {
		// 따로 SCC 저장하는 것은 생략
		while (1) {
			int t = S.top(); S.pop();
			finished[t] = 1;
			SCCnums[t] = SCCcnts;
			if (t == curr) break; // 자신이 나올 때 까지!
		}
		++SCCcnts;
	}

	return result;
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	int N, M; // 변수의 개수, 절의 개수
	cin >> N >> M;
	graph = vector<vector<int>>(N * 2);
	// N = 3 -> 0 ~ 5

	for (int m{}; m < M; ++m) {
		int a, b;
		cin >> a >> b;
		// -1 -> 0, 1 -> 1
		// -2 -> 2, 2 -> 3
		// -3 -> 4, 3 -> 5
		if (a < 0) a = -2 * (a + 1);
		else a = 2 * a - 1;
		if (b < 0) b = -2 * (b + 1);
		else b = 2 * b - 1;
		// 만들 간선
		int notA = (a & 1) == 0 ? a + 1 : a - 1;
		int notB = (b & 1) == 0 ? b + 1 : b - 1;
		graph[notA].push_back(b); // ~a -> b
		graph[notB].push_back(a); // ~b -> a
	}

	orders = vector<int>(N * 2, 0);
	SCCnums = vector<int>(N * 2, 0);
	finished = vector<int>(N * 2, 0);
	// SCC 찾기
	for (int n{}; n < 2 * N; ++n) {
		if (orders[n] == 0) {
			DFS(n);
		}
	}

	bool chk = true;
	for (int n{}; n < N; ++n) {
		// 2n, 2n+1 서로 반대
		// 서로 반대 관계인 정점이 하나라도 하나의 SCC에 속하면 절대로 참이 나올 수 없음.
		int curr = n << 1;
		if (SCCnums[curr] == SCCnums[curr + 1]) {
			chk = false;
			break;
		}
	}
	if (chk) cout << "1\n";
	else cout << "0\n";

	return 0;
}