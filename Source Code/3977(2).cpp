// tarjan
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

vector<vector<int>> graph; // graph

vector<int> visited; // 방문 순서 저장
int dfsnIndex{};

vector<int> isFinish; // SCC가 결정된 경우 true

vector<vector<int>> SCC; // SCC[i] : i번째 SCC에 속한 V들.
vector<int> SCCIndex; // SCCIndex[i] : i번째 정점이 속한 SCC 번호

stack<int> S;

int DFS(int curr) {
	visited[curr] = ++dfsnIndex;
	S.push(curr);

	// curr에서 갈 수 있는 정점 중 dfsn 최소 값을 result에 저장
	int result = visited[curr];
	for (int& next : graph[curr]) {
		if (visited[next] == 0) { // 미방문
			result = min(result, DFS(next));
		}
		else if (!isFinish[next]) {
			result = min(result, visited[next]);
		}
	}

	// 자신이 최소의 dfsn인 경우 -> SCC 추출
	if (result == visited[curr]) {
		vector<int> nowSCC;
		while (!S.empty()) {
			int t = S.top(); S.pop();
			nowSCC.push_back(t);
			SCCIndex[t] = static_cast<int>(SCC.size());
			isFinish[t] = 1;
			if (t == curr) break;
		}
		sort(begin(nowSCC), end(nowSCC));
		SCC.push_back(nowSCC);
	}
	return result;
}

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int T{}; cin >> T;

	while(T--) {
		int N, M; cin >> N >> M; // 정점 수, 간선 수
		
		// 정점 : 1 ~ N
		graph = vector<vector<int>>(N);
		visited = vector<int>(N, 0);
		dfsnIndex = 0;
		isFinish = vector<int>(N, 0);
		vector<vector<int>>().swap(SCC); // swap empty
		SCCIndex = vector<int>(N, 0);

		for (int m{}; m < M; ++m) {
			int a, b; cin >> a >> b;
			graph[a].push_back(b);
		}
		
		for (int n{}; n < N; ++n) {
			if (!visited[n]) {
				DFS(n);
			}
		}

		// SCCNum : SCC 개수
		int SCCNum = static_cast<int>(SCC.size());
		vector<int> SCCIndegree(SCCNum, 0);
		for (int sccidx{}; sccidx < SCCNum; ++sccidx) { // scc마다
			for (int& sccV : SCC[sccidx]) { // sccidx번째 SCC에 속한 정점들마다
				for (int& next : graph[sccV]) {
					if (SCCIndex[next] == sccidx) continue; // 현재랑 같은 SCC
					else SCCIndegree[SCCIndex[next]]++;
				}
			}
		}

		// Indegree가 0개인 SCC가 2개 이상 있는지 확인
		int answerSCC{ -1 };
		for (int sccidx{}; sccidx < SCCNum; ++sccidx) {
			if (SCCIndegree[sccidx] == 0) {
				if (answerSCC == -1) answerSCC = sccidx; // 첫 발견 시 index 갱신
				else {
					answerSCC = -2; // 두 번째 발견 시!
					break;
				}
			}
		}

		if (answerSCC == -2) cout << "Confused\n";
		else {
			for (int& v : SCC[answerSCC]) cout << v << '\n';
		}
		cout << '\n';
	}

	return 0;
}