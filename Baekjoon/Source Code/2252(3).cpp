// 가장 먼저 오는 위상 정렬
// indegree 개수 0인 것부터 - 갱신
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);

	int N, M;
	cin >> N >> M;
	vector<vector<int>> AL(N+1); // 인접 리스트
	vector<int> in_degree(N + 1);
	int A, B;
	for (int m = 0; m < M; ++m) {
		cin >> A >> B;
		AL[A].push_back(B);
		++in_degree[B];
	}
	vector<bool> chk(N + 1, false); // 방문 여부 
	priority_queue<int, vector<int>, greater<int>> PQ; // min_heap
	for (int i = 1; i <= N; ++i) {
		if(!in_degree[i]) PQ.push(i); // in - degree 개수
	}
	while (!PQ.empty()) {
		int now = PQ.top();
		PQ.pop();
		if (chk[now]) continue;
		chk[now] = true;
		cout << now << " ";
		for (auto& i : AL[now]) {
			if (!(--in_degree[i])) PQ.push(i);
		}
	}
	cout << "\n";
	return 0;
}