// https://non-stop.tistory.com/46
// https://hqjang.tistory.com/104
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int N, cnt = 0;
vector<int> edges[1000001];
int visited[1000001];
int DP[1000001][2]{};

// 최소인 얼리 어답터의 개수
// 0 : now index가 얼리어답터x
// 1 : now index가 얼리어답터o

// now : 현재 정점
void dfs(int now) { // 현재 정점
	visited[now] = 1;
	DP[now][1] = 1; // 자기 자신이 얼리어답터
	for (int& next : edges[now]) {
		if (!visited[next]) {
			dfs(next);
			DP[now][0] += DP[next][1]; // 자신이 아니니까 자식은 무조건 얼리어답터.
			DP[now][1] += min(DP[next][0], DP[next][1]); // 자신이 얼리어답터이니 자식은 상관 없음(둘 중에 작은 거)
		}
	}
}

int main() {
	cin.tie(NULL)->sync_with_stdio(false);
	cin >> N;
	for (int i = 0; i < N - 1; ++i) {
		int f, t;
		cin >> f >> t;
		edges[f].push_back(t);
		edges[t].push_back(f);
	}
	
	dfs(1); // root 노드를 임의의 노드로 잡고 시작
	cout << min(DP[1][0], DP[1][1]) << '\n';

	return 0;
}