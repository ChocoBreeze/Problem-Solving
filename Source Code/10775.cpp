#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct UnionFind {
	vector<int> par;
	UnionFind(int n) : par(n, -1) {}
	int Find(int a) {
		if (par[a] < 0) return a;
		return par[a] = Find(par[a]);
	}
	void Union(int a, int b) { // 무조건 a < b이도록 입력
		a = Find(a), b = Find(b);
		if (a == b) return;
		par[a] += par[b]; // a로 합치기
		par[b] = a;
	}
};

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int G; cin >> G; // 게이트 수
	int P; cin >> P; // 비행기 수

	UnionFind uf(G + 1); // 0 ~ G
	int answer{};
	bool finish{};
	for (int p{}; p < P; ++p) {
		int g{}; cin >> g;
		int par = uf.Find(g);
		if (par == 0) { // 더 이상 물러날 곳이 없다!
			finish = true;
		}
		if (!finish) {
			uf.Union(par - 1, par);
			++answer;
		}
	}
	cout << answer << '\n';

	return 0;
}