// 조금 깊게 생각해보기..
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Union_Find {
	vector<int> par, siz;

	Union_Find(int n) : par(n, -1), siz(n, 1) {}

	int root(int x) {
		if (par[x] == -1) return x;
		else return par[x] = root(par[x]);
	}

	bool unite(int x, int y) {
		x = root(x), y = root(y);
		if (x == y) return false;
		if (siz[x] < siz[y]) swap(x, y);
		par[y] = x;
		siz[x] += siz[y];
		return true;
	}
};

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	int N, M, T, tmp;
	cin >> N >> M;
	Union_Find u(N + 1); // 1 ~ N
	cin >> T; // 진실을 아는 사람
	for (int t = 0; t < T; ++t) {
		cin >> tmp;
		u.unite(0, tmp); // 0은 지민
	}
	vector<vector<int>> Ps(M);
	for (int m = 0; m < M; ++m) {
		int P; // 파티에 오는 사람 수
		cin >> P;
		bool chk = true;
		for (int p = 0; p < P; ++p) {
			cin >> tmp;
			Ps[m].push_back(tmp);
			if (u.root(0) == u.root(tmp)) { // 이미 사실을 아는 사람이 온 경우
				chk = false;
			}
		}
		if (!chk) {
			for (auto& p : Ps[m]) {
				u.unite(0, p);
			}
		}
	}
	// 뒤에서 새로 묶인 사람의 경우 반영하지 못함. - 최대 M 번 더 확인이 필요함.
	for (int j = 0; j < M; ++j) {
		for (int m = 0; m < M; ++m) {
			bool chk = true;
			for (auto& p : Ps[m]) {
				if (u.root(0) == u.root(p)) { // 이미 사실을 아는 사람이 온 경우
					chk = false;
				}
			}
			if (!chk) {
				for (auto& p : Ps[m]) {
					u.unite(0, p);
				}
			}
		}
	}
	int answer = 0;
	for (int m = 0; m < M; ++m) {
		bool chk = true;
		for (auto& p : Ps[m]) {
			if (u.root(0) == u.root(p)) {
				chk = false;
				break;
			}
		}
		if (chk) ++answer;
	}
	cout << answer;
	return 0;
}