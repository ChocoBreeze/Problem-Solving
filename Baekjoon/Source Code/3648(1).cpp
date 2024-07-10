// 의심 없이 만들기 = clause
// 상근이는 무조건 진출하기 : 다음 clause 포함 (1 V 1)
// 2-SAT
// tarjan

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

vector<vector<int>> graph;

vector<int> orders, sccN, finished;
int order, sccNum;

stack<int> S;

int DFS(int curr) {
	int ret = orders[curr] = ++order;
	S.push(curr);

	for (int& next : graph[curr]) {
		if (!orders[next]) ret = min(ret, DFS(next));
		else if (!finished[next]) ret = min(ret, orders[next]);
	}

	if (ret == orders[curr]) {
		while (1) {
			int now = S.top(); S.pop();
			finished[now] = 1;
			sccN[now] = sccNum;
			if (now == curr) break;
		}
		++sccNum;
	}

	return ret;
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);

	while (1) {
		int n, m; cin >> n >> m; // 참가자의 수, 심사위원의 수
		if (cin.eof()) break;
		// 참가자의 번호 : 1 ~ n
		
		sccNum = order = 0;
		const int vertexN = n << 1;
		stack<int>().swap(S); // swap empty
		graph = vector<vector<int>>(vertexN); // n <= 1000
		orders = vector<int>(vertexN, 0);
		sccN = vector<int>(vertexN, 0);
		finished = vector<int>(vertexN, 0);

		for (int i{}; i < m; ++i) {
			// -2 => 2 ( a => -2a - 2)
			// 2 => 3 (a => 2a - 1)
			int a{}, b{}; cin >> a >> b;
			a = (a < 0) ? -2 * a - 2 : 2 * a - 1;
			b = (b < 0) ? -2 * b - 2 : 2 * b - 1;
			int revA{a^1}, revB{b^1};
			graph[revA].push_back(b); // ~a -> b
			graph[revB].push_back(a); // ~b -> a
		}
		// 상근이는 항상 포함. (1 v 1)인 간선 만들기
		// 즉, ~1 -> 1
		graph[0].push_back(1);

		for (int v{}; v < vertexN; ++v) {
			if (!orders[v]) {
				DFS(v);
			}
		}
		
		bool chk = [&vertexN]() -> bool {
			for (int v{}; v < vertexN; v += 2) {
				int first = v, second = v + 1;
				if (sccN[first] == sccN[second]) return false;
			}
			return true;
		} ();
		if (chk) cout << "yes\n";
		else cout << "no\n";
	}

	return 0;
}