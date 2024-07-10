// 최단 거리 한 번 구하기 : (E+V)logV
// 모든 간선에 대해 간선 하나씩 지울 때마다 최단 거리 계산 할 수 없음.
// VV(V + E)logE->TLE
// 최단 거리에 속한 간선을 빼야 새 최단 거리 도출이 가능.
// 최단 거리에 속한 간선 수는 최대(V - 1)개
// (V - 1)(E + V)logV 정도 걸릴 듯?

// 최단 경로가 여러 개 나오는 거 같아서 처음에는 경로로 만들 수 있는 모든 간선들에 대해
// 빼서 최단 경로를 구해서 max 구하는 방식을 가져갔는데,
// A라는 최단 경로와 B라는 최단 경로가 있을 때, 간선 e가 B에 속하는 경우에
// e를 뺀다고 해도 A라는 최단 경로를 구할 수 있어서 구하는 의미가 없음.

// 여러 개의 최단 경로를 계산하지 않고 하나만 고려한다.

#include <iostream>
#include <vector> // vector
#include <queue> // queue, priority_queue
#include <algorithm> // max

using namespace std;
const int INF = static_cast<int>(21e8);
struct edge {
	int to;
	int weight;
	edge(int t, int w) : to(t), weight(w) {}
	bool operator< (const edge& other) const {
		return weight > other.weight; // min heap
	}
};

struct edgeInfo {
	int from;
	int to;
	edgeInfo(int f, int t) : from(f), to(t) {}
};

using pii = pair<int, int>;
int N, M;

int dijkstra(vector<vector<edge>>& graph, int from, int to) {
	vector<int> dist(N + 1, INF);
	dist[1] = 0;
	priority_queue<edge> pq;
	pq.push(edge(1, 0));

	while (!pq.empty()) {
		edge now = pq.top();
		pq.pop();

		if (dist[now.to] < now.weight) continue; // 볼 필요 없음

		for (auto& next : graph[now.to]) {
			if ((next.to == from && now.to == to) || (next.to == to && now.to == from)) continue; // 없는 간선 취급
			int nextdist = dist[now.to] + next.weight;
			if (dist[next.to] > nextdist) {
				dist[next.to] = nextdist;
				pq.push(edge(next.to, nextdist));
			}
		}
	}
	return dist[N];
}

int main() {
	cin.tie(NULL)->sync_with_stdio(false);
	cin >> N >> M;
	vector<vector<edge>> graph(N+1); // 1부터 시작
	for (int m = 0; m < M; ++m) {
		int a, b, c;
		cin >> a >> b >> c; // 양방향. (두 정점 사이에는 한 개의 길만 존재.)
		graph[a].push_back(edge(b, c));
		graph[b].push_back(edge(a, c));

	}
	vector<int> dist(N + 1, INF); // 
	vector<int> from(N + 1); // 경로 구하기용
	dist[1] = 0;
	from[1] = -1;
	priority_queue<edge> pq;
	pq.push(edge(1, 0));

	// 최단 거리 구하기
	while (!pq.empty()) {
		edge now = pq.top();
		pq.pop();

		if (dist[now.to] < now.weight) continue;

		for (auto& next : graph[now.to]) {
			int nextdist = dist[now.to] + next.weight;
			if (dist[next.to] > nextdist) {
				dist[next.to] = nextdist;
				from[next.to] = now.to;
				pq.push(edge(next.to, nextdist));
			}
		}
	}

	// 경로 복구(하나의 최단 거리에 사용한 간선 저장)
	int index = N;
	vector<edgeInfo> used_edges; // from - to
	used_edges.reserve(N + 1);
	while (from[index] != -1) {
		used_edges.push_back(edgeInfo(from[index], index));
		index = from[index];
	}
	

	int answer{};

	for (auto& e : used_edges) { // e의 정보는 간선(from, to)
		// e 제외하고 dijkstra
		int d = dijkstra(graph, e.from, e.to);
		if (d == INF) continue; // 못 감
		answer = max(answer, d);
	}
	cout << answer << endl;

	return 0;
}