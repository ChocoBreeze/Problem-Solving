#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct Edge {
	int to, weight;
	Edge(int to, int weight) : to(to), weight(weight) {}
};
constinit const int INF = 1 << 29;

int main() {
	cin.tie(nullptr), ios::sync_with_stdio(false);
	int N, M; // 정점 수(~ 200), 간선 수(~ 20'000)
	cin >> N >> M;

	vector<vector<int>> adjMatrix(N + 1, vector<int>(N + 1, INF));
	vector<vector<Edge>> graph(N + 1);
	for (int n{ 1 }; n <= N; ++n) {
		adjMatrix[n][n] = 0;
	}

	for (int m{}; m < M; ++m) {
		int a, b, c;
		cin >> a >> b >> c; // a -> b (weight = c)
		adjMatrix[a][b] = min(adjMatrix[a][b], c);
		adjMatrix[b][a] = min(adjMatrix[b][a], c);
		graph[a].emplace_back(b, c);
		// graph[b].emplace_back(a, c);
	}

	for (int k{ 1 }; k <= N; ++k) {
		for (int i{ 1 }; i <= N; ++i) {
			for (int j{ 1 }; j <= N; ++j) {
				adjMatrix[i][j] = min(adjMatrix[i][j], adjMatrix[i][k] + adjMatrix[k][j]);
			}
		}
	}

	double answer{ static_cast<double>(INF) };
	for (int s{ 1 }; s <= N; ++s) { // 시작할 점
		double nowAnswer{ -1 };

		for (int n{ 1 }; n <= N; ++n) {
			for (Edge& e : graph[n]) { // to, weight
				// n-> e.to
				int first{ n }, second{ e.to };
				if (adjMatrix[s][first] > adjMatrix[s][second]) {
					swap(first, second);
				}
				double time = adjMatrix[s][first] + (adjMatrix[s][second] - adjMatrix[s][first]) + static_cast<double>(e.weight - adjMatrix[s][second] + adjMatrix[s][first]) / 2;
				// adjMatrix[s][first] - 둘 중 먼저 도착하는 정점 => 즉, 타기 시작하는 시간
				// (adjMatrix[s][second] - adjMatrix[s][first]) => 두번 째 정점에 도착하기 전까지 => 한쪽 방향으로만 타는 시간
				// static_cast<double>(e.weight - adjMatrix[s][second] + adjMatrix[s][first]) / 2 => 둘 다 도착 => 양 방향 모두 타는 시간
				nowAnswer = max(nowAnswer, time);
			}
		}
		answer = min(answer, nowAnswer);
	}

	cout << fixed;
	cout.precision(1);
	cout << answer << '\n';

	return 0;
}