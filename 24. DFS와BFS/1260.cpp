#include<iostream>
#include<vector>
#include<queue>
#include<stack>
#include<algorithm>
int main() {
	std::cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	int N, M, V;
	int v1, v2;
	std::cin >> N >> M >> V;
	std::vector<std::vector<int>> A(N + 1);
	for (int i = 0; i < M; ++i) {
		std::cin >> v1 >> v2;
		A[v1].push_back(v2);
		A[v2].push_back(v1);
	}
	for (int i = 1; i <= N; ++i) {
		std::sort(A[i].begin(), A[i].end());
	}

	std::vector<int> result_stack;
	std::vector<int> result_queue;
	std::vector<int> check(N + 1, 0);
	std::queue<int> Q;
	std::stack<int> S;

	// BFS
	Q.push(V); // start
	while (!Q.empty()) {
		int v = Q.front();
		Q.pop();
		if (check[v] == 1) continue;
		check[v] = 1;
		for (int i = 0; i < A[v].size(); ++i) {
			if (check[A[v][i]] == 0) {
				Q.push(A[v][i]);
			}
		}
		result_queue.push_back(v);
		
	}

	// DFS
	check.assign(N + 1, 0);
	S.push(V); // start
	while (!S.empty()) {
		int v = S.top();
		S.pop();
		if (check[v] == 1) continue;
		check[v] = 1;
		for (int i = A[v].size()-1; i >=0; --i) {
			if (check[A[v][i]] == 0) {
				S.push(A[v][i]);
			}
		}
		result_stack.push_back(v);
		
	}

	// 결과 출력
	for (auto& temp : result_stack) {
		std::cout << temp << " ";
	}
	std::cout << "\n";
	for (auto& temp : result_queue) {
		std::cout << temp << " ";
	}
	return 0;
}