// Network Flow
// ����
// Ford-Fulkerson alg -> O((V+E)f) : f��� �� ������ �־��� ��쿡�� ���� �߻�!
// Edmonds-Karp alg -> O(VE^2) : DFS ��� BFS�� ���� �׶� �׶��� ���� ª�� ��� ã��
// https://m.blog.naver.com/kks227/220804885235 ����

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

constinit const int INF = 1 << 30;
constinit const int SIZE = 52; // 0 ~ 51

// ABCD...Zabcd...z
inline int ToInt(char c) {
	if (c & ' ') return c - 'a' + 26;
	else return c - 'A';
}

struct Edge {
	// rev : (to, from)�� graph[to]���� �� ��° �������
	// cap : capacity
	int rev, from, to, cap;
	Edge(int rev, int from, int to, int cap) : rev(rev), from(from), to(to), cap(cap) {}
};

vector<vector<Edge>> graph; // adjacency list
vector<int> prevVisited;

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	graph = vector<vector<Edge>>(SIZE);

	int N{}; cin >> N; // ���� ����
	for (int n{}; n < N; ++n) {
		char a{}, b{}; int cap{};
		cin >> a >> b >> cap;
		int from = ToInt(a), to = ToInt(b);
		int fromRev = static_cast<int>(graph[from].size());
		int toRev = static_cast<int>(graph[to].size());
		// ��������� �带 �� ����.
		graph[from].emplace_back(toRev, from, to, cap); // ���� ����
		graph[to].emplace_back(fromRev, to, from, cap); // ������ ����
	}

	int s{ 0 }, t{ 25 }; // s(A) -> t(Z)���� ���� maximum flow ã��
	int maximumFlow{};

	while (1) {
		prevVisited.assign(SIZE, -1); // �湮Ȯ�� �� ��𿡼� �Դ��� ����
		vector<pair<int,int>> path(SIZE);// ��λ��� �������� �����صξ� ���߿� ����
		// path[i] : Edge e�� to�� i�� ������ {from, index} ����
		// index : from -> i�� ������ from�� �� ��° index����.
		queue<int> Q;
		Q.push(s);

		while (!Q.empty() && prevVisited[t] == -1) {
			int now = Q.front(); Q.pop();
			int index{};
			for (Edge& e : graph[now]) {
				if (e.cap > 0 && prevVisited[e.to] == -1) {
					Q.push(e.to);
					prevVisited[e.to] = now;
					path[e.to] = make_pair(now, index);
					if (e.to == t) break;
				}
				++index;
			}
		}
		if (prevVisited[t] == -1) break; // �� �̻� augmenting path ���� X

		int flow = INF;
		for (int i = t; i != s; i = prevVisited[i]) { // find maxflow
			Edge& e = graph[path[i].first][path[i].second];
			flow = min(flow, e.cap);
		}
		for (int i = t; i != s; i = prevVisited[i]) {
			Edge& e = graph[path[i].first][path[i].second];
			e.cap -= flow;
			graph[e.to][e.rev].cap += flow;
		}
		maximumFlow += flow;
	}

	cout << maximumFlow << '\n';

	return 0;
}