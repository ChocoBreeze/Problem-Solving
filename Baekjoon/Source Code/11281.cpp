// 공부
// https://m.blog.naver.com/kks227/220803009418
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

vector<vector<int>> graph;

vector<int> finished, orders;
int order;

vector<int> SCCn; // SCCn[i] : i가 속한 scc 번호
int SCCcnt;

stack<int> S;

struct Info {
	int SCCn;
	int nodeN;
	Info(int SCCn, int nodeN) : SCCn(SCCn), nodeN(nodeN) {}
	bool operator< (const Info& other) const {
		return SCCn < other.SCCn;
	}
};
vector<Info> infos;
// infos[i].SCCn : i가 속한 scc 번호
// infos[i].nodeN = i : 정점 번호 - 정렬

int DFS(int curr) {
	int ret = orders[curr] = ++order;
	S.push(curr);

	for (int& next : graph[curr]) {
		if (orders[next] == 0) ret = min(ret, DFS(next)); // 아직 방문 안 한
		else if(!finished[next]) ret = min(ret, orders[next]); // 아직 SCC 구성이 안 끝난
	}

	if (ret == orders[curr]) {
		while (1) {
			int now = S.top(); S.pop();
			finished[now] = 1;
			SCCn[now] = SCCcnt;
			infos[now].SCCn = SCCcnt;
			if (now == curr) break;
		}
		++SCCcnt;
	}


	return ret;
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	int N, M;
	cin >> N >> M;
	graph = vector<vector<int>>(N * 2); // N = 3 -> 0 ~ 5

	for (int m{}; m < M; ++m) {
		int a, b; cin >> a >> b;
		// -1 -> 0, 1 -> 1
		// -2 -> 2, 2 -> 3
		// -3 -> 4, 3 -> 5
		if (a < 0) a = -2 * (a + 1);
		else a = 2 * a - 1;
		if (b < 0) b = -2 * (b + 1);
		else b = 2 * b - 1;
		// 만들 간선
		int notA = (a & 1) == 0 ? a + 1 : a - 1;
		int notB = (b & 1) == 0 ? b + 1 : b - 1;
		graph[notA].push_back(b); // ~a -> b
		graph[notB].push_back(a); // ~b -> a
	}

	orders = vector<int>(N * 2, 0);
	SCCn = vector<int>(N * 2, 0);
	infos = vector<Info>(N * 2, Info(0, 0));
	finished = vector<int>(N * 2, 0);
	// SCC 찾기
	for (int n{}; n < 2 * N; ++n) {
		infos[n].nodeN = n;
		if (orders[n] == 0) {
			DFS(n);
		}
	}

	sort(begin(infos), end(infos));
	// tarjan -> SCC 번호가 크면 클수록 DAG 상에서 앞에 위치함. (DFS 순서를 역으로 계산 = 위상 정렬)

	bool chk = true;
	for (int n{}; n < N; ++n) {
		// 2n, 2n+1 서로 반대
		// 서로 반대 관계인 정점이 하나라도 하나의 SCC에 속하면 절대로 참이 나올 수 없음.
		int curr = n << 1;
		if (SCCn[curr] == SCCn[curr + 1]) {
			chk = false;
			break;
		}
	}

	if (chk) {
		cout << "1\n";
		vector<int> answer(N, -1);
		for (int n{ 2 * N - 1 }; n >= 0; --n) {
			// 먼저 발견되는 정점(a)을 false로 설정!
			// 즉, a -> b 일 때, a를 false로 설정
			int index = infos[n].nodeN;
			index >>= 1; // index의 참 거짓 여부에 상관없이 진짜 index
			// infos[n].nodeN이 홀수 => index가 true => 를 false로 설정
			// infos[n].nodeN이 짝수 => index가 false => 를 true로 설정
			if (answer[index] == -1) answer[index] = !(infos[n].nodeN & 1);
		}

		for (int& an : answer) cout << an << ' ';
		cout << '\n';
	}
	else cout << "0\n";
	
	return 0;
}