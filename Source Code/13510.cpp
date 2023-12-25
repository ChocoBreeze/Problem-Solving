// https://justicehui.github.io/hard-algorithm/2019/02/06/HLD/
// https://www.acmicpc.net/problem/13510
// 첫 글부터..
// 약간의 코드 변경 + 주석

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
constinit const int SEGTREESIZE = 1 << 18;

struct SegTree {
	int tree[SEGTREESIZE], lim;
	void init(int n) {
		for (lim = 1; lim <= n; lim <<= 1); // leaf node 시작점
	}
	void update(int x, int v) { // x의 값을 v로 변경
		x += lim;
		tree[x] = v;
		while (x > 1) {
			x >>= 1;
			tree[x] = max(tree[2 * x], tree[2 * x + 1]);
		}
	}
	int query(int s, int e) { // [s, e] 최대값 구하기
		s += lim, e += lim;
		int ret{}; // 간선의 비용은 항상 1,000,000보다 작거나 같은 자연수이다.
		while (s < e) {
			if (s % 2 == 1) ret = max(ret, tree[s++]);
			if (e % 2 == 0) ret = max(ret, tree[e--]);
			s >>= 1;
			e >>= 1;
		}
		if (s == e) ret = max(ret, tree[s]);
		return ret;
	}
} seg;

using pii = pair<int, int>;
constinit const int SIZE = 101010;

int n, m; // 정점 수, 쿼리 수
int s[SIZE], e[SIZE], c[SIZE]; // i번째 간선 정보 (s[i] -> e[i], c[i] 비용)
vector<pii> g[SIZE]; // 인접리스트 {도착점, 초기비용}

int depth[SIZE], lcaT[20][SIZE]; // depth[i] : i번 정점의 깊이, lcaT : lca table(sparse table)
int par[SIZE], weight[SIZE]; // par[i] : i번 정점의 부모, weight[i] : i번 정점을 자식 정점으로 하는 간선의 무게

// comp[i] : i번 간선이 속하는 무거운 경로 번호(실제로는 간선 인덱스가 아닌 정점 i에 대한 정보)
// head[i] : i번 무거운 간선에서 맨 위에 있는 정점, lab[i] : i번 정점의 DFS ORDER
int comp[SIZE], head[SIZE], lab[SIZE];
int piv1, piv2; // 무거운 경로 번호, dfs order

int newCost[SIZE]; // 간선 2개를 이을 때, DFS 방문 순서로 nxt 정점에 정보 저장.

// 정점의 깊이와 간선의 무게를 구하는 dfs
void dfs(int now, int prv) {
	weight[now] = 1;
	for (auto& i : g[now]) {
		auto& [nxt, cost] = i;
		if (nxt == prv) continue; // 이전 정점 방문 방지
		depth[nxt] = depth[now] + 1; // 다음 정점 depth
		par[nxt] = lcaT[0][nxt] = now; // 바로 위 부모 설정
		newCost[nxt] = cost;
		dfs(nxt, now);
		weight[now] += weight[nxt]; // 간선 무게 누적
	}
}

// 두 번째 dfs, 간선 분류 및 DFS ordering
void hld(int now, int prv) {
	sort(begin(g[now]), end(g[now]), [](const pii& a, const pii& b) {
		return weight[a.first] > weight[b.first];
	}); //간선의 무게를 기준으로 내림차순 정렬

	// 무거운 간선들을 타고 DFS ordering
	int heavy = -1;
	for (auto& i : g[now]) { // 가장 앞에 있는 간선만 무거운 간선
		// 정렬이 된 상태에서 가장 가중치가 큰 간선이 이전 정점으로 돌아갈까봐 해놓은 건가?..
		int nxt = i.first; // 도착점
		if (nxt == prv) continue;
		heavy = nxt;
		comp[nxt] = comp[now]; // i번 간선(정점 nxt)이 속하는 무거운 경로 번호
		lab[nxt] = ++piv2; // nxt번 정점의 DFS ORDER
		hld(nxt, now);
		break;
	}

	// 무거운 간선이 아닌 간선들
	for (auto& i : g[now]) { // 나머지는 가벼운 간선
		int nxt = i.first;
		if (nxt == heavy || nxt == prv) continue;
		comp[nxt] = ++piv1; // nxt이 속하는 무거운 경로 번호
		head[piv1] = nxt; // piv1(현재 무거운 경로)의 맨 위 정점
		lab[nxt] = ++piv2; // nxt번 정점의 DFS ORDER
		hld(nxt, now);
	}
}

// 전형적인 LCA 구하기
int lca(int s, int e) { 
	if (depth[s] > depth[e]) swap(s, e); // s가 더 얕게
	int diff = depth[e] - depth[s];
	for (int i{}; i < 20; ++i) {
		if ((diff >> i) & 1) e = lcaT[i][e];
	}
	for (int i = 19; i >= 0; --i) {
		if (lcaT[i][s] != lcaT[i][e]) s = lcaT[i][s], e = lcaT[i][e];
	}
	if (s == e) return s;
	return lcaT[0][s];
}

void update(int idx, int val) {
	// idx에 해당하는 간선의 양쪽 두 정점 s[idx], e[idx]
	if (depth[s[idx]] > depth[e[idx]]) swap(s[idx], e[idx]);
	seg.update(lab[e[idx]], val); // e[idx]에 해당하는 DFS ORDER와 바꿀 값
}

int sub_query(int s, int e) {
	int ret{};
	while (comp[s] != comp[e]) { // 무거운 경로 번호가 같을 때까지 반복
		int ss = head[comp[s]], ee = head[comp[e]]; // 각 무거운 경로의 방문 순서가 가장 빠른 정점
		// 둘 중 더 깊은 정점을 먼저 계산 후 해당 정점을 다른 무거운 경로로 이동.
		if (depth[ss] > depth[ee]) {
			ret = max(ret, seg.query(lab[ss], lab[s]));
			s = par[ss];
		}
		else {
			ret = max(ret, seg.query(lab[ee], lab[e]));
			e = par[ee];
		}
	}
	// 무거운 경로가 같아진 상태에서
	if (depth[e] < depth[s]) swap(s, e); // s의 depth가 더 가볍도록
	ret = max(ret, seg.query(lab[s] + 1, lab[e]));
	// 왜 lab[s] + 1인가?
	// dfs 방문 순서에서 curr -> next일 때, next 정점에 정보가 저장되어 있음.
	// lab[s]의 정보를 반영하게 되면 원하는 간선 정보가 아니게 됨.
	return ret;
}

int query(int u, int v) {
	int t = lca(u, v);
	// 1. u -> t
	// 2. v -> t
	return max(sub_query(u, t), sub_query(v, t));
}

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(0);
	cin >> n; // 정점 수
	seg.init(n);
	for (int i = 1; i < n; ++i) {
		cin >> s[i] >> e[i] >> c[i];
		g[s[i]].push_back({ e[i], c[i] });
		g[e[i]].push_back({ s[i], c[i] });
	}

	dfs(1, 0); // 정점의 깊이와 간선 무게 설정

	// lca table 만들기.
	for (int i = 1; i < 20; ++i) {
		for (int j = 1; j <= n; ++j) {
			lcaT[i][j] = lcaT[i - 1][lcaT[i - 1][j]];
		}
	}

	head[1] = comp[1] = lab[1] = piv1 = piv2 = 1; // 초기 셋팅
	hld(1, 0);
	for (int i = 2; i <= n; ++i) { // segment Tree setting
		seg.update(lab[i], newCost[i]);
	}
	cin >> m; // query 수
	while (m--) {
		int op; cin >> op;
		if (op == 1) {
			int idx, val; cin >> idx >> val;
			update(idx, val); // 간선 idx의 값을 val로 변경.
		}
		else {
			int u, v; cin >> u >> v;
			cout << query(u, v) << "\n"; // u -> v로 가는 비용 중 가장 큰 것 출력
		}
	}
	return 0;
}