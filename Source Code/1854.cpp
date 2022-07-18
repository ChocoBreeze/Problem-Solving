// dijkstra에서 K번째 경로를 뽑기
// 한 번 갔던 곳도 중복 방문!
#include <iostream>
#include <vector>
#include <queue> // priority_queue

using namespace std;

struct e_t {
	int to;
	int weight;
	e_t(int t, int w) : to(t), weight(w) {}
	bool operator< (const e_t& other) const {
		return this->weight > other.weight; // min heap
	}
};

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	int N, M, K;
	cin >> N >> M >> K;
	vector<vector<e_t>> edges(N + 1);
	int a, b, c;
	for (int m = 0; m < M; ++m) {
		cin >> a >> b >> c;
		edges[a].push_back(e_t(b, c));
	}
	vector<priority_queue<int>> k_dist(N + 1); // max_heap
	k_dist[1].push(0);
	priority_queue<e_t> PQ; // min_heap
	PQ.push(e_t(1, 0));
	while (!PQ.empty()) {
		e_t now = PQ.top();
		PQ.pop();
		for (auto& i : edges[now.to]) {
			int nweight = now.weight + i.weight;
			// 이미 K번째 값이 있는데 새로 구한 값보다 큰 경우 갱신
			if (k_dist[i.to].size() == K && k_dist[i.to].top() > nweight) {
				k_dist[i.to].pop();
			}
			// K번째 보다 작은 개수일 경우 push
			if (k_dist[i.to].size() < K) {
				k_dist[i.to].push(nweight);
				PQ.push(e_t(i.to, nweight));
			}
		}
	}
	for (int i = 1; i <= N;++i) {
		if (k_dist[i].size() < K) cout << "-1\n";
		else cout << k_dist[i].top() << "\n";
	}

	return 0;
}