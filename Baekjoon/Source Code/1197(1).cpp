// prim
// 시작 정점을 기준으로 경계(이전에 방문했던 정점들) 구성.
// 거리가 최소인 정점 선택 -> 정점에 연결된 정점들 거리 갱신 및 정점들 추가.
// 
#include <iostream>
#include <vector>
#include <queue> // min_heap
#include <algorithm>

using namespace std;

const int INF = 100000000;

struct Edge {
	int dst;
	int weight;
	Edge(int dst, int weight) : dst(dst), weight(weight) {}
	inline bool operator< (const Edge& e) const {
		return this->weight < e.weight;
	}
	inline bool operator> (const Edge& e) const {
		return this->weight > e.weight;
	}

};

using Graph = vector<vector<Edge>>;

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	int V, E;
	cin >> V >> E;
	Graph graph(V + 1);
	for (int e = 1; e <= E; ++e) {
		int A, B, C;
		cin >> A >> B >> C; // A -> B (C)
		graph[A].push_back(Edge(B, C));
		graph[B].push_back(Edge(A, C));
	}
	vector<bool> chk(V + 1, false); // 방문 여부
	vector<int> dist(V + 1, INF); // 경계에서 거리 관리
	dist[1] = 0; // 시작 점
	priority_queue<Edge, vector<Edge>, greater<Edge>> PQ;
	for (int i = 1; i <= V; ++i) {
		PQ.push(Edge(i, dist[i]));
	}
	int weight_sum = 0;
	while (!PQ.empty()) {
		auto e = PQ.top(); // 해당하는 정점 + 경계 ~ 정점까지의 거리
		PQ.pop();
		if (chk[e.dst]) continue;
		chk[e.dst] = true;
		weight_sum += dist[e.dst];
		for (auto& i : graph[e.dst]) {
			if (dist[i.dst] > i.weight) {
				dist[i.dst] = i.weight;
				PQ.push(Edge(i.dst, dist[i.dst]));
			}
		}
	}
	cout << weight_sum;
	return 0;
}