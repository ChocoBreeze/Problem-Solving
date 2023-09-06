#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

vector<int> VisitOrder; // 방문 순서 저장
int order = 0; // 방문 순서 저장

struct Edge {
	int from, to;
	Edge(int from, int to) : from(from), to(to) {}
	bool operator<(const Edge& other) const {
		if (this->from == other.from) return this->to < other.to;
		return this->from < other.from;
	}
};

vector<Edge> answer;
vector<vector<int>> graph;

int dfs(int curr, int parent) {
	// 현재 노드의 low 값을 부모에게 반환해야 함.
	VisitOrder[curr] = ++order;
	int minOrder = VisitOrder[curr];

	for (int& next : graph[curr]) {
		if (next == parent) continue; // 부모 - 같은 간선 방지
		if (VisitOrder[next]) { // 이미 방문한 점 (root tree 상 조상)
			minOrder = min(minOrder, VisitOrder[next]);
		}
		else { // 미방문점 (자식)
			int low = dfs(next, curr);
			/*
				next에서 트리, 역방향 간선만을 통해 도달 가능한 최소의 dfsn이 curr의 dfsn보다 크면, 
				next 이하의 정점들로부터 curr 또는 그 위의 정점으로 갈 수단인 간선이 바로 이 간선밖에 없다는 말.
				즉 이 간선이 단절선이라는 말이다.
			*/
			if (VisitOrder[curr] < low) { // 하나라도 존재하는 경우 curr -> next는 단절선
				// curr을 통해서만 갈 수 있는 정점! -> curr은 단절점
				if (curr < next) answer.emplace_back(curr, next);
				else answer.emplace_back(next, curr);
			}
			minOrder = min(minOrder, low);
		}
	}
	return minOrder;
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	int V, E;
	cin >> V >> E;
	
	graph = vector<vector<int>>(V + 1);
	VisitOrder = vector<int>(V + 1, 0); // 방문 순서 저장
	// VisitOrder.assign(V + 1, 0); 
	answer.reserve(V + 1); // push_back 빠르게

	for (int e{}; e < E; ++e) {
		int a, b;  cin >> a >> b; // 양방향
		graph[a].push_back(b);
		graph[b].push_back(a);
	}

	// 연결 그래프가 아니므로 각 정점마다 dfs!
	for (int i = 1; i <= V; ++i) {
		if (!VisitOrder[i]) {
			dfs(i, 0);
		}
	}

	sort(begin(answer), end(answer));
	cout << answer.size() << '\n';
	for (Edge& e : answer) {
		cout << e.from << " " << e.to << '\n';
	}
	return 0;
}