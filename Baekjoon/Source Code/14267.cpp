#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main() {
	int n, m, tmp, tmp_score;
	cin.tie(NULL)->sync_with_stdio(false);
	cin >> n >> m;
	
	vector<vector<int>> adj_list(n);
	for (int i = 0; i < n;++i) {
		cin >> tmp;
		if (tmp == -1) continue;
		tmp--;
		adj_list[tmp].push_back(i);
	}
	
	vector<int> compliments(n, 0);
	for (int i = 0; i < m; ++i) {
		cin >> tmp >> tmp_score;
		compliments[--tmp] += tmp_score;
	}
	
	vector<long long> result(n, 0);
	for (int i = 0; i < n;++i) {
		if (compliments[i] == 0) continue;
		queue<int> Q;
		Q.push(i);
		while (!Q.empty()) {
			int now = Q.front();
			Q.pop();
			result[now] += compliments[i];
			for (auto& n : adj_list[now]) {
				Q.push(n);
			}
		}
	}
	for (auto& v : result) {
		cout << v << " ";
	}
	cout << '\n';
	return 0;
}