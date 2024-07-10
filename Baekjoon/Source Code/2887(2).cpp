// Prim
// 17888KB, 140ms
#include <bits/stdc++.h>

using namespace std;
constexpr int INF = 1000000000;

struct Coord {
	int original_index;
	int pos;
	Coord(int index, int pos) : original_index(index), pos(pos) {}
    bool operator<(const Coord& other) const {
        return this->pos < other.pos;
    }
};

struct Edge {
	int dst;
	int weight;
	Edge(int dst, int weight) : dst(dst), weight(weight) {}
    bool operator> (const Edge& other) const {
        return this->weight > other.weight;
    }
};
using Graph = vector<vector<Edge>>;	

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	int N; cin >> N;
	vector<Coord> xPos(N, Coord(0, 0));
    vector<Coord> yPos(N, Coord(0, 0));
    vector<Coord> zPos(N, Coord(0, 0));
	for (int i{}; i < N; ++i) {
		zPos[i].original_index = yPos[i].original_index = xPos[i].original_index = i;
		cin >> xPos[i].pos >> yPos[i].pos >> zPos[i].pos;
	}
    
    // 모든 정점을 다 돌면서 간선 만들 수 없음.
    // 각 좌표만 비교해서 가깝다 생각하는 간선 만들기
    sort(begin(xPos), end(xPos));
    sort(begin(yPos), end(yPos));
    sort(begin(zPos), end(zPos));

    // 두 행성을 연결하는 비용 = min(|Xa - Xb|, |Ya - Yb|, |Za - Zb|)
    // 각 좌표에 대해 정렬 후 간선 만들어도 됨.

    // 간선 구성
    Graph graph(N);
    for(int i{};i< N - 1;++i) {
        graph[xPos[i].original_index].emplace_back(xPos[i+1].original_index, abs(xPos[i].pos - xPos[i + 1].pos));
        graph[xPos[i + 1].original_index].emplace_back(xPos[i].original_index, abs(xPos[i].pos - xPos[i + 1].pos));
        graph[yPos[i].original_index].emplace_back(yPos[i+1].original_index, abs(yPos[i].pos - yPos[i + 1].pos));
        graph[yPos[i + 1].original_index].emplace_back(yPos[i].original_index, abs(yPos[i].pos - yPos[i + 1].pos));
        graph[zPos[i].original_index].emplace_back(zPos[i+1].original_index, abs(zPos[i].pos - zPos[i + 1].pos));
        graph[zPos[i + 1].original_index].emplace_back(zPos[i].original_index, abs(zPos[i].pos - zPos[i + 1].pos));
    }

    // prim 진행
    int ans{}, nodeCnt{};
    priority_queue<Edge, vector<Edge>, greater<Edge>> pq; // min heap
    vector<int> dist(N, INF), visited(N, 0);
    pq.emplace(0,0);
    dist[0] = 0;
    while(!pq.empty()) {
        if(nodeCnt == N) break; // N개 고름
        Edge now = pq.top(); pq.pop();
        if(visited[now.dst]) continue; // 이전에 추가된 높은 간선의 가중치 거르기
        visited[now.dst] = 1;
        ++nodeCnt;
        ans += now.weight;
        for (Edge& e : graph[now.dst]) {
            if(visited[e.dst]) continue; // 이미 포함된 정점
			if (dist[e.dst] > e.weight) {
				dist[e.dst] = e.weight;
				pq.emplace(e.dst, e.weight);
			}
		}
    }
    cout << ans << '\n';
   
	return 0;
}