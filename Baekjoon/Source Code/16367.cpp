// SCC - kosaraju
// https://justicehui.github.io/icpc/2020/02/10/BOJ16367/ (CNF 구성)
// 2-SAT => 가능한지 판별 + 가능하다면 답 출력
// 3804KB, 12ms
#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <utility>

using namespace std;
using pii = pair<int, int>;

vector<vector<int>> graph, revGraph;
vector<int> visited;
vector<int> sccNums; // Sccnums[i] : i가 속한 SCC 번호
int sccCnt{};

stack<int> S;

struct Info {
	int SCCn, nodeN;
	Info(int SCCn, int nodeN) : SCCn{ SCCn }, nodeN{ nodeN } {}
	bool operator< (const Info& other) const {
		return SCCn < other.SCCn;
	}
};
vector<Info> infos;
// infos[i].SCCn : i가 속한 scc 번호
// infos[i].nodeN = i : 정점 번호 - 정렬

void FillStack(int curr) {
	visited[curr] = 1;
	for (int& next : graph[curr]) {
		if (!visited[next]) {
			FillStack(next);
		}
	}
	S.push(curr);
}

void CalculateSCC(int curr) {
	visited[curr] = 1;
	sccNums[curr] = sccCnt;
	infos[curr].SCCn = sccCnt;
	for (int& next : revGraph[curr]) {
		if (!visited[next]) {
			CalculateSCC(next);
		}
	}
}

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int K{}, N{}; cin >> K >> N; // lamp 수, 사람 수
	const int SIZE = (K << 1);
	sccNums.assign(SIZE, 0);
	infos.assign(SIZE, Info(0, 0));
	visited.assign(SIZE, 0);
	graph = vector<vector<int>>(SIZE);
	revGraph = vector<vector<int>>(SIZE);

	for (int n{}; n < N; ++n) {
		vector<pii> guess(3, {0, 0});
		for (int j{}; j < 3; ++j) {
			char c{}; cin >> guess[j].first >> c;
			if (c == 'B') guess[j].second = 1; // T
		}
		// 2개 이상 만족하는 CNF 구성..
		// A, B, C => (A or B) and (B or C) and (C or A)
		for (int j{}; j < 3; ++j) {
			int A{ guess[j].first * 2 - 1 }, B{ guess[(j + 1) % 3].first * 2 - 1 };
			if (guess[j].second == 0) --A; // Red인 경우 False 변수
			if (guess[(j + 1) % 3].second == 0) --B; // Red인 경우 False 변수
			
			int notA{}, notB{};
			if (A & 1) notA = A - 1;
			else notA = A + 1;
			if (B & 1) notB = B - 1;
			else notB = B + 1;

			// (A or B)
			// 1. ~A -> B
			graph[notA].push_back(B);
			revGraph[B].push_back(notA);

			// 2. ~B -> A
			graph[notB].push_back(A);
			revGraph[A].push_back(notB);
		}
	}
	

	for (int k{}; k < SIZE; ++k) {
		infos[k].nodeN = k;
		if (visited[k] == 0) FillStack(k);
	}
	fill(begin(visited), end(visited), 0);
	
	while (!S.empty()) {
		int now = S.top(); S.pop();
		if (!visited[now]) {
			CalculateSCC(now);
			++sccCnt;
		}
	}

	// 짝수, 홀수 : A, ~A
	for (int k{}; k < K; ++k) {
		int curr{ k << 1};
		if (infos[curr].SCCn == infos[curr + 1].SCCn) {
			cout << "-1\n"; // 모순
			return 0;
		}
	}

	sort(begin(infos), end(infos));
	// DFS 순서를 역으로 계산 => 위상 정렬

	vector<int> answer(K + 1, -1);
	for (int k{}; k < SIZE; ++k) {
		// 먼저 발견되는 정점을 false로 설정.
		// 2 => R : 2, B : 3
		// 3 => R : 4, B : 5
		int index{ (infos[k].nodeN >> 1) + 1 }; // 진짜 lamp index
		if (answer[index] == -1) {
			// 미방문인 경우만 갱신
			if (infos[k].nodeN & 1) answer[index] = 0;
			else answer[index] = 1;
			// infos[n].nodeN이 홀수 => 이는 Blue를 의미 => 하지만 먼저 발견되는 정점을 반대로 넣어야 하니 ~필요
		}
		
	}
	for (int& a : answer) {
		if (a == -1) continue; // answer[0] skip
		if (a == 1) cout << 'B';
		else cout << 'R';
	}
	cout << '\n';

	return 0;
}