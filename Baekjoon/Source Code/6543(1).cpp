// SCC에 속한 정점 찾기
// tarjan
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <unordered_set>

using namespace std;

vector<vector<int>> graph; // graph

vector<int> dfsn; // 방문 순서 저장
int dfsnIndex{};

vector<int> isFinish; // SCC가 결정된 경우 true
stack<int> S;

vector<vector<int>> SCC; // SCC[i] : i번째 SCC에 속한 V들.
vector<unordered_set<int>> SCCcontains; // SCCcontains[i] : i번째 SCC에 속한 V들 저장.(O(1))

int DFS(int curr) {
	dfsn[curr] = ++dfsnIndex;
	S.push(curr);

	// curr에서 갈 수 있는 정점 중 dfsn 최소 값 result에 저장
	int result = dfsn[curr];
	for (int& next : graph[curr]) {
		if (dfsn[next] == 0) {
			// 아직 방문하지 않은 이웃 = 자식 -> 방문해서 최소값 갱신
			result = min(result, DFS(next));
		}
		else if (!isFinish[next]) {
			// 방문은 했으나 아직 SCC로 추출되지는 않은 이웃(꼭 조상이라고는 할 수 없음)
			result = min(result, dfsn[next]); // 기존에 저장된 값 이용
		}
	}

	// 자신, 자신의 자손들이 도달 가능한 제일 높은 정점이 자신일 경우 SCC 추출
	if (result == dfsn[curr]) {
		// 스택에서 자신이 나올 때까지 pop
		vector<int> nowSCC;
		unordered_set<int> nowSCCContains;
		while (!S.empty()) {
			int t = S.top(); S.pop();
			nowSCC.push_back(t);
			nowSCCContains.insert(t);
			isFinish[t] = 1;
			if (t == curr) break;
		}
		SCC.push_back(nowSCC);
		SCCcontains.push_back(nowSCCContains);
	}

	return result; // 최소 dfsn 반환
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	while (1) {
		int n{}, m{};  // 노드의 수, 간선의 수
		cin >> n;
		if (n == 0) break;
		cin >> m;

		vector<vector<int>>().swap(SCC); // empty swap
		vector<unordered_set<int>>().swap(SCCcontains); // empty swap

		// graph.assign(n + 1, vector<int>()); // 1 ~ n
		graph = vector<vector<int>>(n + 1);

		for (int i{}; i < m; ++i) {
			int a, b; cin >> a >> b;
			graph[a].push_back(b); // directed
		}
		dfsn = vector<int>(n + 1, 0);
		isFinish = vector<int>(n + 1, 0);
		
		for (int v{ 1 }; v <= n; ++v) {
			if (dfsn[v] == 0) {
				DFS(v);
			}
		}
		
		vector<int> ans;
		for (int i{}; i < static_cast<int>(SCC.size());++i) {
			bool chk = [i]() -> bool {
				for (int& elem : SCC[i]) {
					for (int& next : graph[elem]) {
						if (SCCcontains[i].find(next)==SCCcontains[i].end()) { // not found
							return false;
						}
					}
				}
				return true;
			} ();
			if (chk) {
				for (int& comp : SCC[i]) {
					ans.push_back(comp);
				}
			}
		}
		
		sort(begin(ans), end(ans));
		for (int& v : ans) cout << v << ' ';
		cout << '\n';
	}
	return 0;
}