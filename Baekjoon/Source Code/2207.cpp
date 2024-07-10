/*
(1 V 1) ^ (-1 V -1)
(2 V 1) ^ (-1 V -2)
모든 학생들이 살 수 있을 때에는 “^_^”을 출력하고, 살 수 없을 때에는 "OTL"을 출력
---
하나라도 만족하는 경우가 있다면 ^_^
하나라도 안 되면 OTL
---
즉, https://www.acmicpc.net/problem/11280 : 랑 같은 문제
2-sat인지 알기!
*/
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

vector<vector<int>> graph;

vector<int> orderV;
int order;

vector<int> finished;

vector<int> SCCn;
int SCCcnt;

stack<int> S;

int DFS(int curr) {
	int ret = orderV[curr] = ++order;
	S.push(curr);
	for (int& next : graph[curr]) {
		if (!orderV[next]) ret = min(ret, DFS(next));
		else if (!finished[next]) ret = min(ret, orderV[next]);
	}

	if (ret == orderV[curr]) {
		while (1) {
			int now = S.top(); S.pop();
			SCCn[now] = SCCcnt;
			finished[now] = 1; 
			if (now == curr) break;
		}
		++SCCcnt;
	}

	return ret;
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	int N, M; // 학생 수(N명) + 가위바위보 횟수(M번)
	cin >> N >> M;
	// 학생수(N)이 아닌 M을 기준으로 정점 만들고 간선 만들어야 함..
	const int vertexNum = M * 2;
	graph = vector<vector<int>>(vertexNum);
	orderV = vector<int>(vertexNum, 0);
	finished = vector<int>(vertexNum, 0);
	SCCn = vector<int>(vertexNum, 0);
	for (int n{}; n < N; ++n) {
		int x, y;
		cin >> x >> y;
		// x가 양수 : x번째에 가위를
		// x가 음수 : x번째에 바위를

		// -1 -> 0(false) | 1 -> 1 (true)
		// -2 -> 2 | 2 -> 3
		// -3 -> 4 | 3 -> 5
		// -n -> -(n+1)*2 = -2n -2
		// n -> 2n - 1
		if (x < 0) x = -2 * x - 2;
		else x = 2 * x - 1;
		if (y < 0) y = -2 * y - 2;
		else y = 2 * y - 1;
		int notX{}, notY{};
		if ((x & 1) == 0) { // false
			notX = x + 1;
		}
		else { // true
			notX = x - 1;
		}
		if ((y & 1) == 0) { // false
			notY = y + 1;
		}
		else { // true
			notY = y - 1;
		}
		graph[notX].push_back(y); // ~x -> y
		graph[notY].push_back(x);
	}

	for (int n{}; n < vertexNum; ++n) {
		if (orderV[n] == 0) {
			DFS(n);
		}
	}

	bool chk{ true };
	for (int n{}; n < M; ++n) {
		// 0(false) - 1(true) => 서로 같은 SCC이면 불가능함.
		// 0 -> 0, 1
		// 1 -> 2, 3
		if (SCCn[2 * n] == SCCn[2 * n + 1]) {
			chk = false;
			break;
		}
	}

	if (chk) cout << "^_^\n";
	else cout << "OTL\n";

	return 0;
}