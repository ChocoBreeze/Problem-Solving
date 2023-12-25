#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;
vector<vector<int>> graph, revGraph;
vector<int> money; // Money[i] : ith 정점이 가지고 있는 돈

vector<bool> visited; // 방문 여부 저장

vector<vector<int>> SCC; // SCC[i] : i번째 SCC에 속한 V들.
vector<int> SCCIndex; // SCCIndex[i] : i번째 정점이 속한 SCC 번호
int SCCCnt{};
stack<int> S;

vector<int> SCCDP, SCCMoney, SCCRestaurant, vRestaurant;
// SCCDP[i] : ith SCC 정보 저장(재방문 방지)
// SCCMoney[i] : ith SCC에서 최대로 얻을 수 있는 돈.
// SCCRestaurant[i] : ith SCC에 식당이 존재하는지
// vRestaurant[i] : 정점 i가 식당인지

void FillStack(int curr) {
	visited[curr] = true;
	for (int& next : graph[curr]) {
		if (!visited[next]) {
			FillStack(next);
		}
	}
	S.push(curr);
}

void CollectConnectedComponents(int curr, vector<int>& components) {
	visited[curr] = true;
	SCCIndex[curr] = SCCCnt;
	// SCCMoney[index] += money[curr];
	components.push_back(curr);

	for (int& next : revGraph[curr]) {
		if (!visited[next]) {
			CollectConnectedComponents(next, components);
		}
	}
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
	SCCCnt = 0;
	graph = vector(SIZE, vector<int>(0, 0));
	revGraph = vector(SIZE, vector<int>(0, 0));
	visited = vector(SIZE, false);
	SCCIndex = vector(SIZE, 0); // SCCIndex = vector<int>(SIZE, 0); // 옛날
	SCC = vector<vector<int>>();
	money = vector<int>(SIZE, 0);
	vRestaurant = vector<int>(SIZE, 0);

	for (int e{}; e < E; ++e) {
		int f, t; cin >> f >> t; // 방향성
		graph[f].push_back(t); // f -> t
		revGraph[t].push_back(f); // t -> f (전치 그래프 생성(방향 바꾸기))
	}

	// 첫 DFS -> Stack에 방문 순서대로 저장
	for (int v{ 1 }; v <= V; ++v) {
		if (!visited[v]) {
			FillStack(v);
		}
		cin >> money[v]; // 입력까지 받기
	}

	// 두 번째 DFS -> SCC 만들기
	fill(begin(visited), end(visited), false); // std::fill
	while (!S.empty()) {
		int now = S.top(); S.pop();
		if (!visited[now]) {
			vector<int> components; // SCC[index]에 추가될 정점들 벡터
			CollectConnectedComponents(now, components);
			sort(begin(components), end(components));
			SCC.push_back(components);
			++SCCCnt;
		}
	}

	int S, P; cin >> S >> P; // 시작점, 식당 개수
	for (int p{}; p < P; ++p) {
		int in; cin >> in;
		vRestaurant[in] = 1;
	}

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