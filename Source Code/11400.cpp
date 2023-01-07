#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

vector<int> VisitOrder;
using Edge = pair<int, int>;
vector<Edge> answer;
int order = 0; // 방문 순서 저장

int dfs(vector<vector<int>>& AL, int curr, int parent) {
	// 현재 노드의 low 값을 부모에게 반환해야 함.
	VisitOrder[curr] = ++order;
	int minOrder = VisitOrder[curr];

	for (int next : AL[curr]) {
		if (next == parent) continue; // 부모
		if (VisitOrder[next]) { // 이미 방문한 점
			minOrder = min(minOrder, VisitOrder[next]);
		}
		else { // 미방문점
			int low = dfs(AL, next, curr);
			if (VisitOrder[curr] < low) { // 하나라도 존재하는 경우 curr -> next는 단절선
				// curr을 통해서만 갈 수 있는 정점! -> curr은 단절점
				if (curr < next) answer.push_back(make_pair(curr, next));
				else answer.push_back(make_pair(next, curr));
			}
			minOrder = min(minOrder, low);
		}
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
	answer.reserve(V + 1);

	for (int e = 0; e < E; ++e) {
		cin >> a >> b; // 양방향
		AL[a].push_back(b);
		AL[b].push_back(a);
	}

	// 연결 그래프가 아니므로 각 정점마다 dfs!
	for (int i = 1; i <= V; ++i) {
		if (!VisitOrder[i]) {
			dfs(AL, i, 0);
		}
	}

	cout << answer.size() << "\n";
	sort(begin(answer), end(answer), [](const Edge& a, const Edge& b) {
		if (a.first == b.first) { // 사전순 정렬
			return a.second < b.second;
		}
		else {
			return a.first < b.first;
		}
	});
	for (auto& a : answer) {
		cout << a.first << " " << a.second << "\n";
	}
	return 0;
}