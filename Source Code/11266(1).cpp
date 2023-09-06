#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> graph;
vector<int> VisitOrder; // VisitOrder[i] : dfs tree에서 i정점의 방문 순서 저장
vector<bool> CutVertex; // CutVertex[i] : i가 단절점인 경우 true
int order = 0; // 방문 순서 저장
int ArticulationPointCnt{};

int dfs(int curr, int parent) {
	// 현재 노드의 low 값을 부모에게 반환해야 함.
	VisitOrder[curr] = ++order;
	int child_cnt{}, minOrder{ VisitOrder[curr] };

	// DFS 트리상에서 리프 노드는 단절점이 아님.
	for (int& next : graph[curr]) {
		if (next == parent) continue; // 부모
		if (VisitOrder[next]) { // 이미 방문한 점
			minOrder = min(minOrder, VisitOrder[next]);
		}
		else { // 미방문점
			if (parent == 0) ++child_cnt;
			int low = dfs(next, curr);
			if (VisitOrder[curr] <= low && parent != 0) { // 하나라도 존재하는 경우 curr은 단절점(curr이 root가 아닐 때)
				// curr을 통해서만 갈 수 있는 정점! -> curr은 단절점
				if (CutVertex[curr] == false) {
					ArticulationPointCnt++; // false -> true일 때만 카운팅
				}
				CutVertex[curr] = true;
			}
			minOrder = min(minOrder, low);
		}
	}
	// root node인 경우 두 개 이상의 서로 다른 BCC와 연결될 경우에만 단절점.
	if (parent == 0 && child_cnt >= 2) {
		CutVertex[curr] = true;
		ArticulationPointCnt++;
	}
	return minOrder;
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	int V, E; cin >> V >> E;
	graph = vector<vector<int>>(V + 1);
	VisitOrder = vector<int>(V + 1, 0); // 방문 순서 저장
	// VisitOrder.assign(V + 1, 0); 
	CutVertex = vector<bool>(V + 1, false); // 각 정점의 단절점 여부 저장
	// CutVertex.assign(V + 1, false); 

	for (int e = 0; e < E; ++e) {
		int a, b; cin >> a >> b;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}

	// 연결 그래프가 아니므로 각 정점마다 dfs!
	for (int i = 1; i <= V; ++i) {
		if (!VisitOrder[i]) {
			dfs(i, 0);
		}
	}

	/*
	vector<int> answer;
	answer.reserve(V + 1);
	for (int i{1}; i <= V; ++i) { // 나중에 정렬하는 것보다 이게 더 쌀 듯?
		if (CutVertex[i]) answer.push_back(i);
	}
	cout << answer.size() << "\n";
	for (int& a : answer) {
		cout << a << " ";
	}
	*/
	cout << ArticulationPointCnt << '\n';
	for (int i{ 1 }; i <= V; ++i) {
		if (CutVertex[i]) cout << i << ' ';
	}
	return 0;
}