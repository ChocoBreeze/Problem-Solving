// negative edge 존재 + 하나의 시작점
// -> Bellman-Ford
#include<iostream>
#include<vector>

// underflow 날까?
const int INF = 1000000000;

struct e_t {
	int dst;
	int time;
	e_t(int d, int t) : dst(d), time(t) {}
};

using namespace std;

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);

	int W, H, G, E;
	while (1) {
		cin >> W >> H;
		if (W == 0 && H == 0) break;
		vector<int> map(W * H, 0);
		cin >> G;
		for (int i = 0; i < G; ++i) {
			int a, b;
			cin >> a >> b;
			map[b * W + a] = -1; // 묘비 표시
		}
		vector<vector<e_t>> Edges(W*H - 1);
		for (int i = 0; i < W * H - 1; ++i) { // make edge - 도착점에는 간선을 만들 필요 없다(바로 탈출)
			if (map[i] == -1) continue;
			// 4방향
			if ((i % W) - 1 >= 0 && map[i - 1] != -1) Edges[i].push_back(e_t(i - 1, 1));
			if ((i % W) + 1 < W && map[i + 1] != -1) Edges[i].push_back(e_t(i + 1, 1));
			if (i - W >= 0 && map[i - W] != -1) Edges[i].push_back(e_t(i - W, 1));
			if (i + W < W * H && map[i + W] != -1) Edges[i].push_back(e_t(i + W, 1));
		}
		cin >> E; // 귀신 구멍
		for (int i = 0; i < E; ++i) {
			int x1, y1, x2, y2, t;
			cin >> x1 >> y1 >> x2 >> y2 >> t;
			int num1 = y1 * W + x1, num2 = y2 * W + x2;
			Edges[num1].clear(); // 귀신 구멍에서 옆으로 못 감.. 이 부분이 문제인듯.
			Edges[num1].push_back(e_t(num2, t)); // 간선 추가
		}

		vector<int> Visited(W * H, INF);
		Visited[0] = 0;
		bool isNegCycle = false;
		for (int i = 0; i < W * H; ++i) { // V
			for (int j = 0; j < size(Edges); ++j) { // E
				for (auto& k : Edges[j]) {
					if (Visited[j] != INF && Visited[k.dst] > Visited[j] + k.time) {
						if (i == W * H - 1) {
							isNegCycle = true;
							break;
						}
						Visited[k.dst] = Visited[j] + k.time;
					}
				}
			}
		}
		if (isNegCycle) { // 과거로 ~
			cout << "Never\n";
		}
		else {
			if (Visited.back() == INF) cout << "Impossible\n";
			else cout << Visited.back() << "\n";
		}
	}
	return 0;
}