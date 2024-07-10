// HLD(Heavy Light Decomposition)
// https://m.blog.naver.com/kks227/221413353934

// �� �迭 ����
// unique_ptr

#include <vector>
#include <iostream>
#include <algorithm> // max
#include <memory> // unique_ptr

using namespace std;

constinit const int INF = 1 << 30;

struct Edge {
	int to, weight, index; // ������, ����ġ, ���� ��ȣ
	Edge(int to, int weight, int index) : to(to), weight(weight), index(index) {}
};

struct SegTree {
	int start;
	vector<int> arr; // ���� �Ҵ� -> ���� �Ҵ�

	// ������
	SegTree(int N) {
		int tmpN = 1;
		while (tmpN < N) tmpN <<= 1;
		tmpN <<= 1;

		arr.assign(tmpN, 0);
		start = tmpN / 2;
	}

	// ���� ������ ���� ���� �Է��� �� ��ü ���׸�Ʈ Ʈ�� ����
	void construct() {
		// u���� v�� ���� �ܼ� ��ο� �����ϴ� ��� �߿��� ���� ū ���� ���
		for (int i = start - 1; i > 0; --i) {
			arr[i] = max(arr[i * 2], arr[i * 2 + 1]);
		}
	}

	// v�� ���� k�� ����
	void update(int v, int k) {
		v += start;
		arr[v] = k;
		while (v > 1) {
			int par = v >> 1, left = par << 1, right = left + 1;
			arr[par] = max(arr[left], arr[right]); // warning..
			v = par;
		}
	}

	// ���� [s, e)�� �ִ밪
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
	// �׷��� ������ �Է¹ް� ��� ��ó���� �ϴ� �Լ�
	void initialize();

	// e�� ������ ����ġ�� k�� �����ϴ� ����
	void update(int e, int k);

	// ���� u�� v ������ ��ο� ���� ���� �� �ִ� ����ġ ��
	int getMax(int u, int v);

	// DFS �Լ� 1ȣ: ����Ʈ�� ũ�� ���ϱ�
	void dfs1(int curr, int prev = -1);

	// DFS �Լ� 2ȣ: ������ �׷��� �и�
	void dfs2(int curr, int prev = -1, int currDepth = 0);

	HeavyLightDecomposition(int N) : dcnt(0), N(N), C(0), tSize(N, 0), dfsn(N,0), adj(vector<vector<Edge>>(N)), child(vector<vector<int>>(N))
		, parent(N,0), depth(N,0), cn(N,0), eVertex(N,0), ST(N), cHead(N,-1), cTail(N,-1) { }

private:
	int N, C, dcnt; // ���� ����, �׷� ����, DFS ī���� ����

	// ���� ���� ��ȣ�� �����ϴ� �迭��
	// int tSize[MAX], dfsn[MAX]; // ����Ʈ�� ũ��, DFS �湮 ����(�� ���� ��ȣ)
	vector<int> tSize, dfsn;
	// vector<Edge> adj[MAX];
	vector<vector<Edge>> adj; // ���� ���� �迭
	// vector<int> child[MAX];
	vector<vector<int>> child; // �ڽ� ���� ���

	// �� ���� ��ȣ�� �����ϴ� �迭��
	// int parent[MAX], depth[MAX], cn[MAX]; // �θ� ���� ��ȣ, ����, �׷� ��ȣ
	vector<int> parent, depth, cn;

	// ���� ��ȣ(1-based) -> �ڽ� ������ �� ���� ��ȣ(0-based)
	// int eVertex[MAX]; // edge index -> vertex index
	vector<int> eVertex;

	// �׷�(ü��) ��ȣ�� �����ϴ� �迭��
	// int cHead[MAX], cTail[MAX]; // �׷쿡�� ���� ���� ���� ��ȣ, ���� ���� ��ȣ
	vector<int> cHead, cTail;

	// ���� �ִ� ���׸�Ʈ Ʈ��
	SegTree ST;
};

// �� ���� DFS�� ���� ��� ������ �и��մϴ�.
void HeavyLightDecomposition::initialize() {
	// �׷��� ���� �Է¹ޱ�: �̶� ���� ��ȣ�� 0���� �ű��.
	// cin >> N;
	for (int i = 1; i < N; ++i) { // edge
		int u, v, w; cin >> u >> v >> w;
		--u, --v;
		adj[u].emplace_back(v, w, i);
		adj[v].emplace_back(u, w, i);
	}
	// ù DFS : �� ������ ����Ʈ�� ũ�� ���ϱ�
	dfs1(0);

	// �θ�, �׷� ���� ���� �ʱ�ȭ
	C = dcnt = 0;
	// fill(cHead, cHead + MAX, -1);
	// fill(cTail, cTail + MAX, -1);
	// �����ڿ��� �ʱ�ȭ
	parent[0] = -1;

	// �� ��° DFS : �� ������ �׷캰�� �з�
	dfs2(0);

	// ���� ����� �ٽ� ���� �ʱ� ���׸�Ʈ Ʈ�� ����
	// ���� 
	for (int n{}; n < N; ++n) {
		int u = dfsn[n];
		for (auto& e : adj[n]) {
			auto& [next, d, en] = e; // to, weight, index
			int v = dfsn[next]; // 0-based
			// �� ������ �� �� ó���ϴ� ���� ���� ����, �� ���� ������ ���ؼ��� ó��
			if (depth[u] < depth[v]) {
				eVertex[en] = v; // ���� ��ȣ(1���� ��)�� ���� ���� ���� ��ȣ�� �˷��ִ� �迭
				ST.arr[ST.start + v] = d; // ���׸�Ʈ Ʈ���� ������ �ʱ�ȭ
				// dfs ������� leaf node ä��.
			}
		}
	}
	ST.construct();
}

// �� ������ ��Ʈ�� �ϴ� ����Ʈ�� ũ�⸸ ���ϱ�
void HeavyLightDecomposition::dfs1(int curr, int prev) {
	tSize[curr] = 1;
	for (auto& p : adj[curr]) {
		auto& [next, d, en] = p;
		if (next != prev) { // ������ ������ �ƴ� ���� DFS �����
			dfs1(next, curr);
			// �ڽ� DFS ��, Ȯ���� �ڽ� ����Ʈ �� ����Ʈ�� ������ ����
			child[curr].push_back(next);
			tSize[curr] += tSize[next];
		}
	}
}

// ������ �׷��� �и�
void HeavyLightDecomposition::dfs2(int curr, int prev, int currDepth) {
	// �� ���� ��ȣ�� DFS ī���� ������ ����
	int u = dfsn[curr] = dcnt++;
	// ���� �׷쿡 �̹� ������ ���Խ�Ŵ
	cn[u] = C;
	// ������ ���̴� �����ε� ��� �� ���̹Ƿ� �� ���� ��ȣ�� ���� �ű�
	depth[u] = currDepth;
	// �̹� �׷��� cHead(���� ��ȣ�� ���� ����, �� ���۹�ȣ), cTail(���� ��ȣ�� ū ����, �� ����ȣ) ����
	if (cHead[C] < 0) cHead[C] = u;
	cTail[C] = u;
	// ���� ����� ��� �̹� �׷��� �ŵ����� ���ư�
	if (child[curr].empty()) {
		++C;
		return;
	}

	// chained: ���ſ� ���� �� ���� ã��(���ſ� ������ ���� ����)
	int chained = child[curr][0];
	for (int& next : child[curr]) { // 0�� �ߺ��̱� �ѵ�..
		if (tSize[chained] < tSize[next]) chained = next;
	}

	// ���ſ� ���� ������ ���� ���� DFS: ���� �׷��� �̾����
	dfs2(chained, curr, currDepth + 1);
	// �θ� ���� ��ȣ ���� ��� ����� ���̹Ƿ� �� ���� ��ȣ�� ���� �ű�
	parent[dfsn[chained]] = u;

	// ������ �������� Ÿ�� �������� DFS�� ���� �� �׷��� ����
	for (int& next : child[curr]) {
		if (next != chained) dfs2(next, curr, currDepth + 1);
		// �θ� ���� �ű�
		int v = dfsn[next];
		parent[v] = u;
	}
}

// ù ����, Ư�� ������ ����ġ �ٲٱ�
void HeavyLightDecomposition::update(int e, int k) {
	ST.update(eVertex[e], k);
}

int HeavyLightDecomposition::getMax(int u, int v) {
	int result = -INF;
	// ���� u, v�� �� ���� ��ȣ�� �ٲ�
	u = dfsn[u]; 
	v = dfsn[v];

	// ���� �ٸ� �׷쿡 ���� �ִ� ����, ���� �� �׷���� �����ذ��� �׷��� ����Ÿ�� �ö��
	if (cn[u] != cn[v]) {
		while (1) {
			// cn[u] : u�� ���� �׷� ��ȣ.
			// cHead[cn[u]] : u�� ���� �׷� ��ȣ���� ���� ���� ����
			int uHead = cHead[cn[u]], vHead = cHead[cn[v]];
			// u�� ���� �׷��� �� ����
			if (depth[uHead] > depth[vHead]) {
				// �׷� �� ���� ����
				result = max(ST.getMax(uHead, u + 1), result);
				// u�� �׷� �� ���� �ٷ� �� �������� �Űܰ�
				u = parent[uHead];
			}
			// v�� ���� �׷��� �� ����
			else {
				// �׷� �� ���� ����
				result = max(ST.getMax(vHead, v + 1), result);
				// v�� �׷� �� ���� �ٷ� �� �������� �Űܰ�
				v = parent[vHead];
			}
			// ���� ���� �׷쿡 ���ϸ� break
			if (cn[u] == cn[v]) break;
		}
	}

	// u�� v�� ���ÿ� ���� (������) �׷� �� ���� ����
	result = max(ST.getMax(min(u, v) + 1, max(u, v) + 1), result);

	// ��� ����
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
