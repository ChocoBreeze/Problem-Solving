#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> VisitOrder;
vector<bool> CutVertex;
int order = 0; // 방문 순서 저장

int dfs(vector<vector<int>>& AL, int curr, int parent) {
	// 현재 노드의 low 값을 부모에게 반환해야 함.
	VisitOrder[curr] = ++order;
	int child_cnt = 0;

	int minOrder = VisitOrder[curr];

	for (int next : AL[curr]) {
		if (next == parent) continue; // 부모
		if (VisitOrder[next]) { // 이미 방문한 점
			minOrder = min(minOrder, VisitOrder[next]);
		}
		else { // 미방문점
			if (parent == 0) ++child_cnt;
			int low = dfs(AL, next, curr);
			if (VisitOrder[curr] <= low && parent != 0) { // 하나라도 존재하는 경우 curr은 단절점
				// curr을 통해서만 갈 수 있는 정점! -> curr은 단절점
				CutVertex[curr] = true;
			}
			minOrder = min(minOrder, low);
		}
	}
	if (parent == 0 && child_cnt >= 2) {
		CutVertex[curr] = 1;
	}
	return minOrder;
}

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	int V, E, a, b;
	cin >> V >> E;
	vector<vector<int>> AL(V + 1);
	VisitOrder.assign(V + 1, 0); // 방문 순서 저장
	CutVertex.assign(V + 1, false); // 각 정점의 단절점 여부 저장

	for (int e = 0; e < E; ++e) {
		cin >> a >> b;
		AL[a].push_back(b);
		AL[b].push_back(a);
	}

	// 연결 그래프가 아니므로 각 정점마다 dfs!
	for (int i = 1; i <= V; ++i) {
		if (!VisitOrder[i]) {
			dfs(AL, i, 0);
		}
	}

	vector<int> answer;
	answer.reserve(V + 1);
	for (int i = 1; i <= V; ++i) {
		if (CutVertex[i]) answer.push_back(i);
	}
	cout << answer.size() << "\n";
	for (auto& a : answer) {
		cout << a << " ";
	}
	return 0;
}