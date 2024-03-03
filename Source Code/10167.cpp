// 공부
// https://m.blog.naver.com/PostView.naver?isHttpsRedirect=true&blogId=edenooo&logNo=221415337560

// Segment Tree
// Divide And Conquer
// O(N^2logN)
// 2572KB, 912ms

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
constinit const int INF = 1 << 30;
using pii = pair<int, int>;
using ll = long long;

struct Point {
	int x, y, w; // 위치 : x,y | 이익 또는 손해 : w
	Point(int x = 0, int y = 0, int w = 0) : x{ x }, y{ y }, w{ w } {}
};

/*
* here.sum = left.sum + right.sum
* here.lmax = max(left.lmax, left.sum + right.lmax)
* here.rmax = max(right.rmax, right.sum + left.rmax)
* here.tmax = max(left.tmax, right.tmax, left.rmax + right.lmax)
*/
struct Info { // SegTree용 구조체
	ll sum, lmax, rmax, tmax;
	Info(ll sum = 0, ll lmax = 0, ll rmax = 0, ll tmax = 0) : sum{ sum }, lmax{ lmax }, rmax{ rmax }, tmax{ tmax } {}
};

vector<Info> seg;
Info Update(int idx, int val, int n, int l, int r) {
	// 범위 밖
	if (r < idx || idx < l) return seg[n];

	// leaf node(업데이트할 위치 도달)
	if (l == r && l == idx) {
		seg[n].sum += val, seg[n].lmax += val, seg[n].rmax += val, seg[n].tmax += val;
		return seg[n];
	}

	int mid = l + ((r - l) >> 1);
	Info left{}, right{};
	left = Update(idx, val, n << 1, l, mid);
	right = Update(idx, val, (n << 1) + 1, mid + 1, r);

	seg[n].sum = left.sum + right.sum;
	seg[n].lmax = max(left.lmax, left.sum + right.lmax);
	seg[n].rmax = max(right.rmax, right.sum + left.rmax);
	seg[n].tmax = max({ left.tmax, right.tmax, left.rmax + right.lmax });
	return seg[n];
}

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);

	int N{}; cin >> N;
	vector<Point> ps(N, Point());
	vector<pii> xs(N, make_pair(0, 0)), ys(N, make_pair(0, 0));
	for (int n{}; n < N;++n) {
		auto& p = ps[n]; cin >> p.x >> p.y >> p.w;
		xs[n] = { p.x, n }; // x위치, index
		ys[n] = { p.y, n }; // y위치, index
	}
	sort(begin(xs), end(xs)); // x 오름차순 정렬
	sort(begin(ys), end(ys)); // y 오름차순 정렬

	// 좌표 압축
	int maxX{};
	for (int n{}; n < N; ++n) { // x
		if (n > 0 && xs[n - 1].first != xs[n].first) ++maxX; // 이전 좌표와 다른 x값인 경우
		ps[xs[n].second].x = maxX;
	}

	int maxY{};
	for (int n{}; n < N; ++n) { // y
		if (n > 0 && ys[n - 1].first != ys[n].first) ++maxY; // 이전 좌표와 다른 y값인 경우
		ps[ys[n].second].y = maxY;
	}

	const int SIZE = maxY + 1;
	vector yy(SIZE, vector<pii>()); // 0 ~ maxY
	for (int n{}; n < N; ++n) { // 좌표압축된 y에 대해 x, w 정보 넣기
		yy[ps[n].y].emplace_back(ps[n].x, ps[n].w);
	}

	int tmpN{1};
	while (tmpN < N) tmpN <<= 1;
	tmpN <<= 1;

	ll answer{};
	for (int sy{}; sy < SIZE; ++sy) { // y start
		seg.assign(tmpN, Info{});
		for (int ey{ sy }; ey < SIZE; ++ey) { // sweeping
			for (auto& [hx, hw] : yy[ey]) {
				// int idx, int val, int n, int l, int r
				Update(hx, hw, 1, 0, N - 1); // 금광 추가 - 최대 O(N^2)번 수행
			}
			answer = max(answer, seg[1].tmax); // 최대 O(N^2)번 수행
		}
	}

	cout << answer << '\n';
	return 0;
}