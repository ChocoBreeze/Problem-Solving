// https://m.blog.naver.com/kks227/220802519976
// Tarjan's algorithm
// 3608KB, 24ms

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;
using Graph = vector<vector<int>>;
Graph graph;

vector<int> dfsn; // 방문 순서 저장
vector<int> sn; // sn[i] : 정점 i가 속한 SCC 번호
vector<bool> isFinish; // SCC가 결정된 정점인 경우 true

int dfsnIndex; // dfsn 카운팅
int SCCCnt; // SCC 개수
vector<vector<int>> SCC; // SCC[i] : i번째 SCC에 속한 V들.
stack<int> S;

constinit const int MAX = 10000;

/**
* 자신의 결과값 리턴
*/
int DFS(int curr) {
	dfsn[curr] = ++dfsnIndex; 
	S.push(curr);

	// curr에서 갈 수 있는 정점 중 dfsn 최소 값 result에 저장
	int result = dfsn[curr];
	for (int& next : graph[curr]) {
		if (dfsn[next] == 0) {
			// 아직 방문하지 않은 이웃 = 자식 -> 방문해서 최소값 갱신
			result = min(result, DFS(next));
		}
		else if(!isFinish[next]) {
			// 방문은 했으나 아직 SCC로 추출되지는 않은 이웃(꼭 조상이라고는 할 수 없음)
			result = min(result, dfsn[next]); // 기존에 저장된 값 이용
		}
	}

	// 자신, 자신의 자손들이 도달 가능한 제일 높은 정점이 자신일 경우 SCC 추출
	if (result == dfsn[curr]) {
		// 스택에서 자신이 나올 때까지 pop
		vector<int> nowSCC;
		while (!S.empty()) {
			int t = S.top(); S.pop();
			nowSCC.push_back(t);
			isFinish[t] = true;
			sn[t] = SCCCnt;
			if (t == curr) break;
		}
		SCC.push_back(nowSCC);
		sort(begin(SCC[SCCCnt]), end(SCC[SCCCnt])); // 답 출력을 위해서
		++SCCCnt;
	}

	return result; // 최소 dfsn 반환
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	int V, E; cin >> V >> E;
	graph.assign(V + 1, vector<int>()); // 1 ~ V
	dfsn.assign(V + 1, 0);
	sn = vector<int>(V + 1, 0);
	isFinish.assign(V + 1, false);

	for (int e{}; e < E; ++e) {
		int f, t; cin >> f >> t; // 방향성
		graph[f].push_back(t); // f -> t
	}

	// 각 정점마다 DFS하면서 SCC 추출.
	// 연결 그래프가 아닐 수도 있으므로 반복문 필요
	for (int v{1}; v <= V; ++v) {
		if (dfsn[v] == 0) { // 아직 미방문
			DFS(v);
		}
	}
	sort(begin(SCC), end(SCC)); // 이거 정렬 기준이 뭐지..

	cout << SCCCnt << '\n'; // SCC 개수
	// 각 SCC 출력
	for (vector<int>& row : SCC) {
		for (int& v : row) {
			cout << v << ' ';
		}
		cout << "-1\n";
	}

	return 0;
}