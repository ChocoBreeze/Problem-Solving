// 중위 순회 - 트리 복구
#include <iostream>
#include <vector>

using namespace std;
vector<int> vertex;
vector<vector<int>> result;
int V, K;

void DFS(int curr, int level, int first, int last) {
	result[level].push_back(vertex[curr]);
	if (level + 1 == K) return; // leaf
	DFS((first + curr - 1) / 2, level + 1, first, curr - 1);
	DFS((curr + 1 + last) / 2, level + 1, curr + 1, last);
}

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	cin >> K;
	result = vector < vector<int>>(K);
	V = (1 << K) - 1;
	vertex = vector<int>(V, 0);
	for (int& v : vertex) cin >> v;
	DFS(V >> 1, 0, 0, V - 1);

	for (int l{}; l < K; ++l) {
		for (int& v : result[l]) {
			cout << v << ' ';
		}
		cout << '\n';
	}

	return 0;
}