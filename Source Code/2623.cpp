// topological sort
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	int N, M; // 가수의 수(정점), 보조 PD의 수 
	// N은 1이상 1,000이하의 정수이고, M은 1이상 100이하의 정수이다.
	cin >> N >> M;
	vector<int> innode(N + 1, 0);
	vector<vector<int>> graph(N + 1);
	for (int m{}; m < M; ++m) {
		int in; cin >> in;
		int lastV{ -1 }; cin >> lastV;
		for (int i{1}; i < in; ++i) {
			int v; cin >> v;
			innode[v]++;
			graph[lastV].push_back(v);
			lastV = v;
		}
	}

	// 답이 여럿일 경우에는 아무거나 하나를 출력 한다. 
	// 만약 남일이가 순서를 정하는 것이 불가능할 경우에는 첫째 줄에 0을 출력한다.
	queue<int> q;
	for (int i{1}; i <= N; ++i) {
		if (innode[i] == 0) {
			q.push(i);
		}
	}
	vector<int> ans;
	ans.reserve(N);
	while (!q.empty()) {
		int now = q.front(); q.pop();
		// cout << now << '\n';
		ans.push_back(now);
		for (int& next : graph[now]) {
			innode[next]--;
			if (innode[next] == 0) q.push(next);
		}
	}

	if (static_cast<int>(ans.size()) != N) cout << "0\n";
	else {
		for (int& v : ans) cout << v << '\n';
	}

	return 0;
}