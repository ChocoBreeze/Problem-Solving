/*
컴퓨터 N(=vertex) 신뢰하는 관계 M(=edge)
A B : A가 B를 신뢰한다 = B를 해킹하면 A도 해킹된다.
B -> A의 의미
*/

#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>

using std::cout;
using std::cin;
using std::vector;
using std::queue;


using Graph = vector<vector<int>>;

int bfs(Graph& graph, int N, int start) {
	vector<bool> visited (N + 1, false);
	queue<int> Q;
	int count = 1; // 자기 자신
	Q.push(start);
	visited[start] = true;
	while (!Q.empty()) {
		int now = Q.front();
		Q.pop();
		for (auto& i : graph[now]) {
			if (!visited[i]) {
				visited[i] = true;
				count++;
				Q.push(i);
			}
		}
	}
	return count;
}

int main() {
	cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	int N, M;
	cin >> N >> M;
	Graph graph(N + 1); // 1 ~ N
	for (int i = 0; i < M; ++i) {
		int A, B;
		cin >> A >> B;
		graph[B].push_back(A);
	}
	int max = -1;
	vector<int> answer;
	for (int i = 1; i <= N; ++i) {
		int answer_i = bfs(graph, N, i);
		if (max <= answer_i) {
			if (max < answer_i && !answer.empty()) answer.clear();
			max = answer_i;
			answer.push_back(i);
		}
	}
	for (auto& i : answer) {
		cout << i << " ";
	}

	return 0;
}