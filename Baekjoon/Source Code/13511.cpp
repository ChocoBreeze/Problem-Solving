#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;
using ll = long long;
constinit const int SIZE = 18; // 1 << 17 = 131072

struct Edge {
	int to, weight;
	Edge(int to, int weight) : to(to), weight(weight) {}
};
vector<vector<Edge>> graph;

ll Query(vector<int>& depth, vector<vector<int>>& sparseT, vector<vector<ll>>& sparseSum) {
	int op{}; cin >> op;
	int u, v, k{}; cin >> u >> v;
	--u, --v;
	int uCopy{ u }, vCopy{ v };
	if (op == 2) {
		cin >> k; 
		--k;
	}

	ll answer{};
	int uToLCA{}, vToLCA{};
	bool uDeep{};
	if (depth[u] > depth[v]) { // v가 더 깊게
		swap(u, v);
		uDeep = true;
	}
	int diff = depth[v] - depth[u];
	for (int d{}; diff > 0; ++d, diff >>= 1) {
		if (diff & 1) {
			answer += sparseSum[v][d];
			v = sparseT[v][d];
			if (uDeep) uToLCA |= (1 << d);
			else vToLCA |= (1 << d);
		}
	}

	while (u != v) {
		int d{};
		for (; d < SIZE; ++d) {
			if (sparseT[u][d] == sparseT[v][d]) break;
		}
		if (d) --d;
		answer += sparseSum[v][d];
		answer += sparseSum[u][d];
		v = sparseT[v][d];
		u = sparseT[u][d];
		uToLCA += (1 << d);
		vToLCA += (1 << d);
	}
	if (op == 2) {
		if (uToLCA == k) answer = u + 1LL;
		else if (uToLCA > k) {
			// u를 올리면서 k번째 찾기 (복사해둔 u 사용)
			for (int d{}; k > 0; k >>= 1, ++d) {
				if (k & 1) uCopy = sparseT[uCopy][d];
			}
			answer = uCopy + 1LL;
		}
		else {
			// v를 올리면서 k번째 찾기
			k = uToLCA + vToLCA - k;
			for (int d{}; k > 0; k >>= 1, ++d) {
				if (k & 1) vCopy = sparseT[vCopy][d];
			}
			answer = vCopy + 1LL;
		}
	}

	return answer;
}

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int N{}; cin >> N;
	graph = vector<vector<Edge>>(N); // 0 ~ N - 1 
	for (int n{ 1 }; n < N; ++n) {
		int t, f, w; cin >> t >> f >> w;
		--t, --f;
		graph[t].emplace_back(f, w);
		graph[f].emplace_back(t, w);
	}

	vector<int> depth(N, 0);
	vector<vector<int>> sparseT(N, vector<int>(SIZE, 0));
	vector<vector<ll>> sparseSum(N, vector<ll>(SIZE, 0));
	depth[0] = 1;
	queue<int> q;
	q.push(0);
	while (!q.empty()) {
		int now = q.front(); q.pop();
		for (Edge& e : graph[now]) {
			if (depth[e.to]) continue;
			depth[e.to] = depth[now] + 1;
			sparseT[e.to][0] = now;
			sparseSum[e.to][0] = e.weight;
			q.push(e.to);
		}
	}
	
	for (int s = 1; s < SIZE; ++s) {
		for (int n{}; n < N; ++n) {
			sparseT[n][s] = sparseT[sparseT[n][s - 1]][s - 1];
			sparseSum[n][s] = sparseSum[n][s-1] + sparseSum[sparseT[n][s - 1]][s - 1];
		}
	}

	int M{}; cin >> M;
	while (M--) {
		ll answer = Query(depth, sparseT, sparseSum);
		cout << answer << '\n';
	}

	return 0;
}