// https://justicehui.github.io/hard-algorithm/2019/02/06/HLD/
// https://www.acmicpc.net/problem/13510
// ù �ۺ���..
// �ణ�� �ڵ� ���� + �ּ�

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
constinit const int SEGTREESIZE = 1 << 18;

struct SegTree {
	int tree[SEGTREESIZE], lim;
	void init(int n) {
		for (lim = 1; lim <= n; lim <<= 1); // leaf node ������
	}
	void update(int x, int v) { // x�� ���� v�� ����
		x += lim;
		tree[x] = v;
		while (x > 1) {
			x >>= 1;
			tree[x] = max(tree[2 * x], tree[2 * x + 1]);
		}
	}
	int query(int s, int e) { // [s, e] �ִ밪 ���ϱ�
		s += lim, e += lim;
		int ret{}; // ������ ����� �׻� 1,000,000���� �۰ų� ���� �ڿ����̴�.
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

int n, m; // ���� ��, ���� ��
int s[SIZE], e[SIZE], c[SIZE]; // i��° ���� ���� (s[i] -> e[i], c[i] ���)
vector<pii> g[SIZE]; // ��������Ʈ {������, �ʱ���}

int depth[SIZE], lcaT[20][SIZE]; // depth[i] : i�� ������ ����, lcaT : lca table(sparse table)
int par[SIZE], weight[SIZE]; // par[i] : i�� ������ �θ�, weight[i] : i�� ������ �ڽ� �������� �ϴ� ������ ����

// comp[i] : i�� ������ ���ϴ� ���ſ� ��� ��ȣ(�����δ� ���� �ε����� �ƴ� ���� i�� ���� ����)
// head[i] : i�� ���ſ� �������� �� ���� �ִ� ����, lab[i] : i�� ������ DFS ORDER
int comp[SIZE], head[SIZE], lab[SIZE];
int piv1, piv2; // ���ſ� ��� ��ȣ, dfs order

int newCost[SIZE]; // ���� 2���� ���� ��, DFS �湮 ������ nxt ������ ���� ����.

// ������ ���̿� ������ ���Ը� ���ϴ� dfs
void dfs(int now, int prv) {
	weight[now] = 1;
	for (auto& i : g[now]) {
		auto& [nxt, cost] = i;
		if (nxt == prv) continue; // ���� ���� �湮 ����
		depth[nxt] = depth[now] + 1; // ���� ���� depth
		par[nxt] = lcaT[0][nxt] = now; // �ٷ� �� �θ� ����
		newCost[nxt] = cost;
		dfs(nxt, now);
		weight[now] += weight[nxt]; // ���� ���� ����
	}
}

// �� ��° dfs, ���� �з� �� DFS ordering
void hld(int now, int prv) {
	sort(begin(g[now]), end(g[now]), [](const pii& a, const pii& b) {
		return weight[a.first] > weight[b.first];
	}); //������ ���Ը� �������� �������� ����

	// ���ſ� �������� Ÿ�� DFS ordering
	int heavy = -1;
	for (auto& i : g[now]) { // ���� �տ� �ִ� ������ ���ſ� ����
		// ������ �� ���¿��� ���� ����ġ�� ū ������ ���� �������� ���ư���� �س��� �ǰ�?..
		int nxt = i.first; // ������
		if (nxt == prv) continue;
		heavy = nxt;
		comp[nxt] = comp[now]; // i�� ����(���� nxt)�� ���ϴ� ���ſ� ��� ��ȣ
		lab[nxt] = ++piv2; // nxt�� ������ DFS ORDER
		hld(nxt, now);
		break;
	}

	// ���ſ� ������ �ƴ� ������
	for (auto& i : g[now]) { // �������� ������ ����
		int nxt = i.first;
		if (nxt == heavy || nxt == prv) continue;
		comp[nxt] = ++piv1; // nxt�� ���ϴ� ���ſ� ��� ��ȣ
		head[piv1] = nxt; // piv1(���� ���ſ� ���)�� �� �� ����
		lab[nxt] = ++piv2; // nxt�� ������ DFS ORDER
		hld(nxt, now);
	}
}

// �������� LCA ���ϱ�
int lca(int s, int e) { 
	if (depth[s] > depth[e]) swap(s, e); // s�� �� ���
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
	// idx�� �ش��ϴ� ������ ���� �� ���� s[idx], e[idx]
	if (depth[s[idx]] > depth[e[idx]]) swap(s[idx], e[idx]);
	seg.update(lab[e[idx]], val); // e[idx]�� �ش��ϴ� DFS ORDER�� �ٲ� ��
}

int sub_query(int s, int e) {
	int ret{};
	while (comp[s] != comp[e]) { // ���ſ� ��� ��ȣ�� ���� ������ �ݺ�
		int ss = head[comp[s]], ee = head[comp[e]]; // �� ���ſ� ����� �湮 ������ ���� ���� ����
		// �� �� �� ���� ������ ���� ��� �� �ش� ������ �ٸ� ���ſ� ��η� �̵�.
		if (depth[ss] > depth[ee]) {
			ret = max(ret, seg.query(lab[ss], lab[s]));
			s = par[ss];
		}
		else {
			ret = max(ret, seg.query(lab[ee], lab[e]));
			e = par[ee];
		}
	}
	// ���ſ� ��ΰ� ������ ���¿���
	if (depth[e] < depth[s]) swap(s, e); // s�� depth�� �� ��������
	ret = max(ret, seg.query(lab[s] + 1, lab[e]));
	// �� lab[s] + 1�ΰ�?
	// dfs �湮 �������� curr -> next�� ��, next ������ ������ ����Ǿ� ����.
	// lab[s]�� ������ �ݿ��ϰ� �Ǹ� ���ϴ� ���� ������ �ƴϰ� ��.
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
	cin >> n; // ���� ��
	seg.init(n);
	for (int i = 1; i < n; ++i) {
		cin >> s[i] >> e[i] >> c[i];
		g[s[i]].push_back({ e[i], c[i] });
		g[e[i]].push_back({ s[i], c[i] });
	}

	dfs(1, 0); // ������ ���̿� ���� ���� ����

	// lca table �����.
	for (int i = 1; i < 20; ++i) {
		for (int j = 1; j <= n; ++j) {
			lcaT[i][j] = lcaT[i - 1][lcaT[i - 1][j]];
		}
	}

	head[1] = comp[1] = lab[1] = piv1 = piv2 = 1; // �ʱ� ����
	hld(1, 0);
	for (int i = 2; i <= n; ++i) { // segment Tree setting
		seg.update(lab[i], newCost[i]);
	}
	cin >> m; // query ��
	while (m--) {
		int op; cin >> op;
		if (op == 1) {
			int idx, val; cin >> idx >> val;
			update(idx, val); // ���� idx�� ���� val�� ����.
		}
		else {
			int u, v; cin >> u >> v;
			cout << query(u, v) << "\n"; // u -> v�� ���� ��� �� ���� ū �� ���
		}
	}
	return 0;
}