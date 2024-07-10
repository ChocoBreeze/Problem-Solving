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
	int N, M; // ���� ��(~ 200), ���� ��(~ 20'000)
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
	for (int s{ 1 }; s <= N; ++s) { // ������ ��
		double nowAnswer{ -1 };

		for (int n{ 1 }; n <= N; ++n) {
			for (Edge& e : graph[n]) { // to, weight
				// n-> e.to
				int first{ n }, second{ e.to };
				if (adjMatrix[s][first] > adjMatrix[s][second]) {
					swap(first, second);
				}
				double time = adjMatrix[s][first] + (adjMatrix[s][second] - adjMatrix[s][first]) + static_cast<double>(e.weight - adjMatrix[s][second] + adjMatrix[s][first]) / 2;
				// adjMatrix[s][first] - �� �� ���� �����ϴ� ���� => ��, Ÿ�� �����ϴ� �ð�
				// (adjMatrix[s][second] - adjMatrix[s][first]) => �ι� ° ������ �����ϱ� ������ => ���� �������θ� Ÿ�� �ð�
				// static_cast<double>(e.weight - adjMatrix[s][second] + adjMatrix[s][first]) / 2 => �� �� ���� => �� ���� ��� Ÿ�� �ð�
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