// https://github.com/kks227/BOJ/blob/master/16000/16074.cpp
// 25208KB, 1272ms

#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <utility>
#include <algorithm>

using namespace std;
using P = pair<int, int>;

struct UnionFind {
	vector<int> p;
	UnionFind(int N) : p(N, -1) { }
	int f(int a) {
		if (p[a] < 0) return a;
		return p[a] = f(p[a]);
	}
	bool u(int a, int b) {
		a = f(a), b = f(b);
		if (a == b) return false;
		if (p[a] > p[b]) swap(a, b);
		p[a] += p[b];
		p[b] = a;
		return true;
	}
};

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int R{}, C{}, Q{}; cin >> R >> C >> Q;
	set<int> S;
	vector h(R, vector<int>(C, 0)), q(Q, vector<int>(2, 0));
	for (int r{}; r < R; ++r) {
		for (int c{}; c < C; ++c) {
			cin >> h[r][c];
			S.insert(h[r][c]); // 가중치별 중복 제거 + 정렬
		}
	}

	vector<int> H2I(S.size(), 0);
	int HI{}, SIZE = R * C; // HI : 최대 가중치 index - 1
	unordered_map<int, int> I2H; // {가중치 크기, 오름차순 정렬 시 위치}
	for (const int& i : S) {
		H2I[HI] = i;
		I2H[i] = HI++;
	}
	vector<P> open(SIZE, make_pair(0, 0)); // {해당하는 가중치의 오름차순 정렬 시 위치, 좌표값 변환한 위치}
	for (int r{}; r < R; ++r) {
		for (int c{}; c < C; ++c) {
			open[r * C + c] = P(I2H[h[r][c]], r * C + c);
		}
	}
	sort(begin(open), end(open)); // 가중치 크기 대로 정렬 (해당 위치 저장)

	vector<int> lo(Q, 0), hi(Q, HI + 1);
	for (int i{}; i < Q; ++i) {
		int r1{}, c1{}, r2{}, c2{}; cin >> r1 >> c1 >> r2 >> c2;
		--r1; --c1; --r2; --c2;
		q[i][0] = r1 * C + c1;
		q[i][1] = r2 * C + c2;
		lo[i] = I2H[max(h[r1][c1], h[r2][c2])];
	}

	while (1) {
		bool flag{};
		vector G(HI + 1, vector<int>());
		for (int i = 0; i < Q; ++i) {
			if (lo[i] + 1 < hi[i]) {
				flag = true;
				int mid = lo[i] + ((hi[i] - lo[i]) >> 1);
				G[mid].push_back(i);
			}
		}
		if (!flag) break;

		UnionFind UF(SIZE);
		for (int i{}, j{}; i < HI; ++i) {
			do {
				auto& [w, u] = open[j]; // 가중치 순으로 정렬된 좌표별로 확인(index, 좌표의 id)
				if (w > i) break; // 현재확인하기로 한 인덱스는 max i
				int r = u / C, c = u % C; // 원래 위치 복원
				for (int d{}; d < 4; ++d) {
					int nr = r + "0211"[d] - '1', nc = c + "1102"[d] - '1';
					if (nr < 0 || nr >= R || nc < 0 || nc >= C) continue;
					if (I2H[h[nr][nc]] <= w) UF.u(u, nr * C + nc); // 새 위치의 좌표에 대한 인덱스도 w보다 작거나 같은 경우에 => Union
				}
			} while (++j < SIZE);
			for (int& k : G[i + 1]) {
				(UF.f(q[k][0]) == UF.f(q[k][1]) ? hi : lo)[k] = i + 1;
			}
		}
	}

	for (int i{}; i < Q; ++i) {
		cout << H2I[hi[i] - 1] << '\n';
	}

	return 0;
}