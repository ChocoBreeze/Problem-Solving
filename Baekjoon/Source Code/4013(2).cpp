#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;
vector<vector<int>> graph;
vector<int> money; // Money[i] : ith 정점이 가지고 있는 돈

vector<int> visited; // 방문 순서 저장
int dfsnIndex{};

vector<int> isFinish; // SCC가 결정된 경우 true

vector<vector<int>> SCC; // SCC[i] : i번째 SCC에 속한 V들.
vector<int> SCCIndex; // SCCIndex[i] : i번째 정점이 속한 SCC 번호
int SCCCnt{};
stack<int> S;

vector<int> SCCDP, SCCMoney, SCCRestaurant, vRestaurant;
// SCCDP[i] : ith SCC 정보 저장(재방문 방지)
// SCCMoney[i] : ith SCC에서 최대로 얻을 수 있는 돈.
// SCCRestaurant[i] : ith SCC에 식당이 존재하는지
// vRestaurant[i] : 정점 i가 식당인지

int FindSCC(int curr) {
	visited[curr] = ++dfsnIndex;
	S.push(curr);

	// curr에서 갈 수 있는 정점 중 dfsn 최소 값을 result에 저장
	int result = visited[curr];
	for (int& next : graph[curr]) {
		if (visited[next] == 0) { // 미방문
			result = min(result, FindSCC(next));
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

int DFS(int curr) {
	int currSCC = SCCIndex[curr];

	bool isTerminal{true}; // 더 이상 갈 데 없는 마지막 노드
	int maxRet{-2}; // 다음 SCC에서 얻을 수 있는 최대 돈
	for (int& v : SCC[currSCC]) {
		for (int& next : graph[v]) {
			int nextSCC = SCCIndex[next];
			if (currSCC == nextSCC) continue; // same SCC
			isTerminal = false; // 다른 SCC로 이동 가능
			if (SCCDP[nextSCC] == -2) maxRet = max(maxRet, DFS(next));
			// else if (SCCDP[nextSCC] == -1) maxRet = max(max; // next를 거쳐서 갈 수 있는 식당이 없을 때
			else maxRet = max(maxRet, SCCDP[nextSCC]);
		}
	}

	if (isTerminal) {
		if (SCCRestaurant[currSCC]) return SCCDP[currSCC] = SCCMoney[currSCC];
		return SCCDP[currSCC] = -1; // 여기가 식당이 아님.
	}
	else {
		if (maxRet == -1) {
			// 갈 수 있는 SCC 중에 Restaurant가 한 곳도 없다.
			if (SCCRestaurant[currSCC]) return SCCDP[currSCC] = SCCMoney[currSCC]; // 현재 SCC가 식당인 경우
			else return SCCDP[currSCC] = -1;
		}
		else {
			// 갈 수 있는 SCC 중에 식당이 존재한다.
			return SCCDP[currSCC] = SCCMoney[currSCC] + maxRet;
		}
	}
}

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int V, E; cin >> V >> E;

	// 정점 : 1 ~ V
	// Edge 개수 : E개
	const int SIZE = V + 1;
	graph = vector(SIZE, vector<int>(0, 0));
	visited = vector(SIZE, 0);
	dfsnIndex = 0;
	isFinish = vector(SIZE, 0);
	SCCIndex = vector(SIZE, 0); // SCCIndex = vector<int>(SIZE, 0); // 옛날
	SCC = vector<vector<int>>();
	money = vector<int>(SIZE, 0);
	vRestaurant = vector<int>(SIZE, 0);

	for (int e{}; e < E; ++e) {
		int f, t; cin >> f >> t; // 방향성
		graph[f].push_back(t); // f -> t
	}

	for (int v{ 1 }; v <= V; ++v) {
		if (!visited[v]) {
			FindSCC(v);
		}
		cin >> money[v]; // 입력까지 받기
	}

	int S, P; cin >> S >> P; // 시작점, 식당 개수
	for (int p{}; p < P; ++p) {
		int in; cin >> in;
		vRestaurant[in] = 1;
	}

	SCCCnt = static_cast<int>(SCC.size());
	SCCDP = vector<int>(SCCCnt, -2); // 금액이 0원도 된다..
	SCCMoney = vector<int>(SCCCnt, 0);
	SCCRestaurant = vector<int>(SCCCnt, 0);
	for (int i{}; i < SCCCnt; ++i) {
		for (int& v : SCC[i]) {
			SCCMoney[i] += money[v]; // 해당 SCC에 속하는 돈 누적
			SCCRestaurant[i] |= vRestaurant[v]; // 하나라도 식당이 있다면
		}
	}

	int answer = DFS(S);
	cout << answer << '\n';

	return 0;
}