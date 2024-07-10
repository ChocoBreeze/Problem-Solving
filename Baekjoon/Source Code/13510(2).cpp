// HLD(Heavy Light Decomposition)
// https://m.blog.naver.com/kks227/221413353934

// 생 배열 제거
// unique_ptr

#include <vector>
#include <iostream>
#include <algorithm> // max
#include <memory> // unique_ptr

using namespace std;

constinit const int INF = 1 << 30;

struct Edge {
	int to, weight, index; // 도착점, 가중치, 간선 번호
	Edge(int to, int weight, int index) : to(to), weight(weight), index(index) {}
};

struct SegTree {
	int start;
	vector<int> arr; // 정적 할당 -> 동적 할당

	// 생성자
	SegTree(int N) {
		int tmpN = 1;
		while (tmpN < N) tmpN <<= 1;
		tmpN <<= 1;

		arr.assign(tmpN, 0);
		start = tmpN / 2;
	}

	// 리프 노드들의 값을 먼저 입력한 후 전체 세그먼트 트리 구축
	void construct() {
		// u에서 v로 가는 단순 경로에 존재하는 비용 중에서 가장 큰 것을 출력
		for (int i = start - 1; i > 0; --i) {
			arr[i] = max(arr[i * 2], arr[i * 2 + 1]);
		}
	}

	// v의 값을 k로 변경
	void update(int v, int k) {
		v += start;
		arr[v] = k;
		while (v > 1) {
			int par = v >> 1, left = par << 1, right = left + 1;
			arr[par] = max(arr[left], arr[right]); // warning..
			v = par;
		}
	}

	// 구간 [s, e)의 최대값
	int getMax(int s, int e) { return getMax(s, e, 1, 0, start); }
	int getMax(int s, int e, int node, int ns, int ne) {
		if (e <= ns || ne <= s) return -1;
		if (s <= ns && ne <= e) return arr[node];

		int mid = ns + (ne - ns) / 2;
		return max(getMax(s, e, node * 2, ns, mid), getMax(s, e, node * 2 + 1, mid, ne));
	}
};

class HeavyLightDecomposition {
public:
	// 그래프 정보를 입력받고 모든 전처리를 하는 함수
	void initialize();

	// e번 간선의 가중치를 k로 갱신하는 연산
	void update(int e, int k);

	// 정점 u와 v 사이의 경로에 속한 간선 중 최대 가중치 값
	int getMax(int u, int v);

	// DFS 함수 1호: 서브트리 크기 구하기
	void dfs1(int curr, int prev = -1);

	// DFS 함수 2호: 간선을 그룹들로 분리
	void dfs2(int curr, int prev = -1, int currDepth = 0);

	HeavyLightDecomposition(int N) : dcnt(0), N(N), C(0), tSize(N, 0), dfsn(N,0), adj(vector<vector<Edge>>(N)), child(vector<vector<int>>(N))
		, parent(N,0), depth(N,0), cn(N,0), eVertex(N,0), ST(N), cHead(N,-1), cTail(N,-1) { }

private:
	int N, C, dcnt; // 정점 개수, 그룹 개수, DFS 카운터 변수

	// 원래 정점 번호로 참조하는 배열들
	// int tSize[MAX], dfsn[MAX]; // 서브트리 크기, DFS 방문 순서(새 정점 번호)
	vector<int> tSize, dfsn;
	// vector<Edge> adj[MAX];
	vector<vector<Edge>> adj; // 인접 간선 배열
	// vector<int> child[MAX];
	vector<vector<int>> child; // 자식 정점 목록

	// 새 정점 번호로 참조하는 배열들
	// int parent[MAX], depth[MAX], cn[MAX]; // 부모 정점 번호, 깊이, 그룹 번호
	vector<int> parent, depth, cn;

	// 간선 번호(1-based) -> 자식 정점의 새 정점 번호(0-based)
	// int eVertex[MAX]; // edge index -> vertex index
	vector<int> eVertex;

	// 그룹(체인) 번호로 참조하는 배열들
	// int cHead[MAX], cTail[MAX]; // 그룹에서 제일 얕은 정점 번호, 깊은 정점 번호
	vector<int> cHead, cTail;

	// 구간 최댓값 세그먼트 트리
	SegTree ST;
};

// 두 번의 DFS에 거쳐 모든 간선을 분리합니다.
void HeavyLightDecomposition::initialize() {
	// 그래프 내용 입력받기: 이때 정점 번호는 0부터 매긴다.
	// cin >> N;
	for (int i = 1; i < N; ++i) { // edge
		int u, v, w; cin >> u >> v >> w;
		--u, --v;
		adj[u].emplace_back(v, w, i);
		adj[v].emplace_back(u, w, i);
	}
	// 첫 DFS : 각 정점의 서브트리 크기 구하기
	dfs1(0);

	// 부모, 그룹 관련 변수 초기화
	C = dcnt = 0;
	// fill(cHead, cHead + MAX, -1);
	// fill(cTail, cTail + MAX, -1);
	// 생성자에서 초기화
	parent[0] = -1;

	// 두 번째 DFS : 각 간선을 그룹별로 분류
	dfs2(0);

	// 간선 목록을 다시 보며 초기 세그먼트 트리 구축
	// 같은 
	for (int n{}; n < N; ++n) {
		int u = dfsn[n];
		for (auto& e : adj[n]) {
			auto& [next, d, en] = e; // to, weight, index
			int v = dfsn[next]; // 0-based
			// 한 간선을 두 번 처리하는 것을 막기 위해, 더 깊은 정점에 대해서만 처리
			if (depth[u] < depth[v]) {
				eVertex[en] = v; // 간선 번호(1부터 셈)를 보고 깊은 정점 번호를 알려주는 배열
				ST.arr[ST.start + v] = d; // 세그먼트 트리의 리프값 초기화
				// dfs 순서대로 leaf node 채움.
			}
		}
	}
	ST.construct();
}

// 각 정점을 루트로 하는 서브트리 크기만 구하기
void HeavyLightDecomposition::dfs1(int curr, int prev) {
	tSize[curr] = 1;
	for (auto& p : adj[curr]) {
		auto& [next, d, en] = p;
		if (next != prev) { // 지나온 정점이 아닐 때만 DFS 계속함
			dfs1(next, curr);
			// 자식 DFS 후, 확실한 자식 리스트 및 서브트리 사이즈 갱신
			child[curr].push_back(next);
			tSize[curr] += tSize[next];
		}
	}
}

// 간선을 그룹들로 분리
void HeavyLightDecomposition::dfs2(int curr, int prev, int currDepth) {
	// 새 정점 번호를 DFS 카운터 변수로 붙임
	int u = dfsn[curr] = dcnt++;
	// 현재 그룹에 이번 정점을 포함시킴
	cn[u] = C;
	// 정점의 깊이는 앞으로도 계속 쓸 것이므로 새 정점 번호에 대해 매김
	depth[u] = currDepth;
	// 이번 그룹의 cHead(제일 번호가 작은 정점, 즉 시작번호), cTail(제일 번호가 큰 정점, 즉 끝번호) 갱신
	if (cHead[C] < 0) cHead[C] = u;
	cTail[C] = u;
	// 리프 노드일 경우 이번 그룹을 매듭짓고 돌아감
	if (child[curr].empty()) {
		++C;
		return;
	}

	// chained: 무거운 간선 한 개를 찾음(무거운 간선을 가진 정점)
	int chained = child[curr][0];
	for (int& next : child[curr]) { // 0번 중복이긴 한데..
		if (tSize[chained] < tSize[next]) chained = next;
	}

	// 무거운 간선 쪽으로 제일 먼저 DFS: 현재 그룹을 이어붙임
	dfs2(chained, curr, currDepth + 1);
	// 부모 정점 번호 역시 계속 사용할 것이므로 새 정점 번호에 대해 매김
	parent[dfsn[chained]] = u;

	// 나머지 간선들을 타고 내려가며 DFS를 통해 새 그룹을 만듦
	for (int& next : child[curr]) {
		if (next != chained) dfs2(next, curr, currDepth + 1);
		// 부모 정점 매김
		int v = dfsn[next];
		parent[v] = u;
	}
}

// 첫 쿼리, 특정 간선의 가중치 바꾸기
void HeavyLightDecomposition::update(int e, int k) {
	ST.update(eVertex[e], k);
}

int HeavyLightDecomposition::getMax(int u, int v) {
	int result = -INF;
	// 먼저 u, v를 새 정점 번호로 바꿈
	u = dfsn[u]; 
	v = dfsn[v];

	// 서로 다른 그룹에 속해 있는 동안, 깊은 쪽 그룹부터 참조해가며 그룹을 갈아타며 올라옴
	if (cn[u] != cn[v]) {
		while (1) {
			// cn[u] : u가 속한 그룹 번호.
			// cHead[cn[u]] : u가 속한 그룹 번호에서 가장 빠른 정점
			int uHead = cHead[cn[u]], vHead = cHead[cn[v]];
			// u가 속한 그룹이 더 깊음
			if (depth[uHead] > depth[vHead]) {
				// 그룹 내 구간 연산
				result = max(ST.getMax(uHead, u + 1), result);
				// u를 그룹 맨 위의 바로 위 정점으로 옮겨감
				u = parent[uHead];
			}
			// v가 속한 그룹이 더 깊음
			else {
				// 그룹 내 구간 연산
				result = max(ST.getMax(vHead, v + 1), result);
				// v를 그룹 맨 위의 바로 위 정점으로 옮겨감
				v = parent[vHead];
			}
			// 둘이 같은 그룹에 속하면 break
			if (cn[u] == cn[v]) break;
		}
	}

	// u와 v가 동시에 속한 (마지막) 그룹 내 구간 연산
	result = max(ST.getMax(min(u, v) + 1, max(u, v) + 1), result);

	// 결과 리턴
	return result;
}



int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int N{}; cin >> N;
	// HeavyLightDecomposition* hld = new HeavyLightDecomposition(N);
	unique_ptr<HeavyLightDecomposition> hld(new HeavyLightDecomposition(N));
	hld->initialize();

	
	int M{}; cin >> M;
	for (int m{}; m < M; ++m) {
		int op{}; cin >> op;
		if (op == 1) { 
			int i{}, c{}; cin >> i >> c;
			hld->update(i, c);
		}
		else { // op == 2
			int u{}, v{}; cin >> u >> v;
			--u, --v;
			int ret = hld->getMax(u, v);
			if (ret == -1) ret = 0; // u == v
			cout << ret << '\n';
		}
	}

	return 0;
}
