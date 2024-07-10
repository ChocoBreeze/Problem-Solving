// kosaraju
// 3272KB, 236ms
#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <utility>
#include <algorithm>

using namespace std;
using pii = pair<int, int>;
constinit const int INF = 1 << 29;

int n{};
stack<int> S;
vector<vector<int>> graph, revGraph;
vector<vector<int>> SCC; // SCC[i] : i번째 SCC에 속한 V들.
vector<int> SCCIndex; // SCCIndex[i] : i번째 정점이 속한 SCC 번호
vector<int> visited;
int index{};

void FillStack(int curr) {
	visited[curr] = 1;

	for (int next{}; next < n; ++next) {
		if (graph[curr][next] && !visited[next]) {
			FillStack(next);
		}
	}

	S.push(curr);
}

void CollectConnectedComponents(int curr, vector<int>& components) {
	visited[curr] = true;
	SCCIndex[curr] = index;
	components.push_back(curr);

	for (int next{}; next < n; ++next) {
		if (revGraph[curr][next] && !visited[next]) {
			CollectConnectedComponents(next, components);
		}
	}
}

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int T{}; cin >> T;

	while (T--) {
		cin >> n;
		index = 0;
		SCC = vector<vector<int>>();
		SCCIndex.assign(n, 0);
		visited.assign(n, 0);
		graph.assign(n, vector<int>(n, 0)), revGraph.assign(n, vector<int>(n, 0));
		for (int i{}; i < n; ++i) {
			string str; cin >> str;
			for (int j{}; j < n; ++j) {
				int v = str[j] - '0';
				graph[i][j] = v;
				revGraph[j][i] = v;
			}
		}

		for (int i{}; i < n; ++i) {
			if (!visited[i]) {
				FillStack(i);
			}
		}

		fill(begin(visited), end(visited), 0); // std::fill
		while (!S.empty()) {
			int now = S.top(); S.pop();
			if (!visited[now]) {
				vector<int> components; // SCC[index]에 추가될 정점들 벡터
				CollectConnectedComponents(now, components);
				SCC.push_back(components);
				++index;
			}
		}

		vector<pii> answer;
		// SCC 내에서 cycle 만들기.
		for (auto& scc : SCC) {
			if (static_cast<int>(scc.size()) == 1) continue;
			for (int s{}, e{ static_cast<int>(scc.size()) }; s < e; ++s) {
				answer.emplace_back(scc[s] + 1, scc[(s + 1) % e] + 1);
			}
		}

		// SCC 간 경로 만들기 : Floyd-Warshall
		// 위상 정렬로 만드는 경우에 
		// indegree가 0일 때만 갱신 => 중간에 간선은 무시됨.
		// indegree가 깎일 때마다 갱신 => 필요 없는 간선도 만들어짐.
		vector sccMat(index, vector<int>(index, INF));
		// SCC 간에 경로 생성
		for (int i{}; i < n; ++i) {
			int now{ SCCIndex[i] };
			sccMat[now][now] = 0; // 자기 자신
			for (int j{}; j < n; ++j) {
				if (graph[i][j]) {
					int next = SCCIndex[j];
					if (now != next) {
						sccMat[now][next] = 1;
					}
				}
			}
		}

		for (int k{}; k < index; ++k) {
			for (int i{}; i < index; ++i) {
				for (int j{}; j < index; ++j) {
					if (sccMat[i][j] == 1 && sccMat[i][k] == 1 && sccMat[k][j] == 1) {
						// i -> j로 갈 수 있고, i -> k -> j로 갈 수 있다면 i -> j 간선 제거
						sccMat[i][j] = INF;
					}
				}
			}
		}

		for (int i{}; i < index; ++i) {
			for (int j{}; j < index; ++j) {
				if (sccMat[i][j] == 1) answer.emplace_back(SCC[i][0] + 1, SCC[j][0] + 1);
			}
		}

		cout << answer.size() << '\n';
		for (auto& a : answer) cout << a.first << ' ' << a.second << '\n';
		cout << '\n';
	}
	return 0;
}