/*
maximum number of non-connected parts from that the network may consist 
after removal of one of the joining points (not counting the removed joining point itself).
즉, 이 프로그램은 접합점 중 하나를 제거한 후 
네트워크가 구성할 수 있는 연결되지 않은 부품의 최대 수를 결정해야 합니다(제거된 접합점 자체는 계산하지 않음)
(해당 단절점이 속한 bcc 개수 + 해당 단절점이 속하지 않은 bcc 개수) 최대값
간선이 하나도 없는 경우(C>=0)에 대해서도 고려하기
*/
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

vector<vector<int>> graph;

vector<int> dfsn; // 방문 순서
int order{};

struct Edge {
	int from, to;
	Edge(int from, int to) : from(from), to(to) {}
	bool operator==(const Edge& other) const { // 뒤에 const 키워드 붙이기!
		return this->from == other.from && this->to == other.to;
	}
};

stack<Edge> S; // BCC를 구성하게 될 Edge들 저장
vector<vector<Edge>> bcc;
vector<int> bccCnt; // bccCnt[i] : i가 속한 bcc 개수
vector<int> articulationPoint; // articulationPoint[i] : i가 단절점인가?

int DFS(int curr, int parent) {
	// return 값 = curr에서 갈 수 있는 최소의 dfsn값
	int result = dfsn[curr] = ++order;
	int cnt{};

	for (int& next : graph[curr]) {
		if (parent == next) continue; // 중복 간선 방지

		// 아직 방문하지 않은 간선
		if (dfsn[curr] > dfsn[next]) S.push(Edge(curr, next));

		if (dfsn[next] != 0) result = min(result, dfsn[next]); // 이미 감
		else { // 미 방문
			int ret = DFS(next, curr);
			result = min(result, ret); // 새 최솟값 갱신

			if (ret >= dfsn[curr]) { // curr보다 조상노드로 갈 수 없음 => 새 BCC(curr에서)
				if (parent != -1) { // 바로 단절점
					articulationPoint[curr] = 1;
				}
				++cnt;
				// 간선 (curr, next)까지 pop
				++bccCnt[curr];
				Edge target(curr, next);
				while (!S.empty() && !(target == S.top())) { // S.empty() 없어도 될 듯?
					S.pop();
				}
				S.pop();
			}
		}
	}

	if (parent != -1 && articulationPoint[curr]) {
		// 이 정점이 루트가 아니라면 최종적으로 1을 더 늘려서 인접한 BCC 개수를 얻을 수 있음..(?)
		bccCnt[curr]++;
	}

	if (parent == -1 /* && cnt > 1 */) {
		// 실제로 단절점 계산할 때는 cnt가 2개 이상인 경우에만 세어야 하지만..
		// 해당 문제에서는 간선 개수가 0개일 수도 있기 때문에 해당 부분 처리를 위해..
		articulationPoint[curr] = 1;
	}

	return result;
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	while (1) {
		int V, E; cin >> V >> E;
		if (V == 0 && E == 0) break;

		graph = vector<vector<int>>(V); // 0 ~ V - 1
		dfsn = vector<int>(V, 0);
		bccCnt = vector<int>(V, 0);
		articulationPoint = vector<int>(V, 0);

		for (int e{}; e < E; ++e) {
			int a, b; cin >> a >> b;
			graph[a].push_back(b);
			graph[b].push_back(a);
		}

		int tot{};
		for (int v{}; v < V; ++v) {
			if (dfsn[v] == 0) {
				tot++;
				DFS(v, -1);
			}
		}
		// cout << tot + *max_element(begin(bccCnt), end(bccCnt)) - 1 << '\n';
		int ans{};
		for (int v{}; v < V; ++v) {
			if (articulationPoint[v]) {
				ans = max(ans, tot + bccCnt[v] - 1);
			}
		}
		cout << ans << '\n';
	}
	return 0;
}