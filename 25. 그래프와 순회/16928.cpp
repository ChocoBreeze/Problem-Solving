#include<iostream>
#include<vector>
#include<queue>

using std::queue;
using std::vector;
using std::cin;
using std::cout;
using Graph = vector<vector<int>>;

struct Vertex {
	int number; // 1 ~ 100
	int count; // number까지 걸린 횟수
	Vertex(int number, int count) : number(number), count(count) {}
};

int main() {
	cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	int N, M, x, y;
	cin >> N >> M;
	Graph graph(101); // 1 ~ 100
	for (int i = 0; i < N; ++i) { // 사다리
		cin >> x >> y;
		graph[x].push_back(y);
	}
	for (int i = 0; i < M; ++i) { // 뱀
		cin >> x >> y;
		graph[x].push_back(y);
	}
	
	int answer = -1;
	queue<Vertex> Q;
	vector<bool> visited(101, false); // 1 ~100
	Q.push(Vertex(1,0)); // start
	visited[1] = true;
	while (!Q.empty()) {
		Vertex now = Q.front();
		if (now.number == 100) break;
		Q.pop();
		for (int i = 1; i <= 6; ++i) {
			int next_vertex = now.number + i; // 다음 vertex
			if (next_vertex == 100) answer = now.count + 1; // 답을 찾음
			if (next_vertex > 100) continue; // 100보다 큰 것은 못 감
			if (visited[next_vertex]) continue; // 이미 방문 완료
			if (graph[next_vertex].size() != 0) Q.push(Vertex(graph[next_vertex][0], now.count + 1)); // 사다리와 뱀 동시에 2개를 가지고 있는 것은 없음.
			else Q.push(Vertex(next_vertex, now.count + 1));
			visited[next_vertex] = true;
		}
		if (answer != -1) break;
	}
	cout << answer;
	return 0;
}