#include<iostream>
#include<vector>
#include<queue>

using namespace std;

void search(vector<vector<int>>& graph, vector<vector<bool>>& result, int s) {
	queue<int> Q;
	Q.push(s);
	while (!Q.empty()) {
		int now = Q.front();
		Q.pop();
		for (auto& i : graph[now]) {
			if (!result[s][i]) {
				Q.push(i);
				result[s][i] = true;
			}
		}
	}
}

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	int N;
	cin >> N;
	vector<vector<int>> graph(N);
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			int temp;
			cin >> temp;
			if (temp == 1) graph[i].push_back(j);
		}
	}
	vector<vector<bool>> result(N, vector<bool>(N, 0));
	for (int i = 0; i < N; ++i) {
		search(graph, result, i);
	}
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N;++j) {
			cout << result[i][j] << " ";
		}
		cout << "\n";
	}
	return 0;
}