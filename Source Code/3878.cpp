// Graham Scan
// 2028KB, 8ms
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using ll = long long;

struct Point {
	int x, y;
	Point(int x, int y) : x{ x }, y{ y } {}
	Point operator-(const Point& other) const;
	bool operator<(const Point& p) const { // x를 우선으로 x가 같으면 y 비교
		return y != p.y ? y < p.y : x < p.x;
	}
};
using Vector = Point;
using Polygon = vector<Point>;

Point Point::operator-(const Point& other) const
{
	return Point(this->x - other.x, this->y - other.y);
}

ll Dot(const Vector& v1, const Vector& v2) {
	return 1LL * v1.x * v2.x + 1LL * v1.y * v2.y;
}
ll Cross(const Vector& v1, const Vector& v2) {
	return 1LL * v1.x * v2.y - 1LL * v1.y * v2.x;
}
ll Norm(const Vector& v) {
	return 1LL * v.x * v.x + 1LL * v.y * v.y;
}

constinit const int ON_SEGMENT = 0;
constinit const int CLOCKWISE = -1;
constinit const int COUNTER_CLOCKWISE = 1;
constinit const int ONLINE_FRONT = -2;
constinit const int ONLINE_BACK = 2;
int CCW(const Point& p0, const Point& p1, const Point& p2) {
	Vector a = p1 - p0;
	Vector b = p2 - p0;
	if (Cross(a, b) > 0LL) return COUNTER_CLOCKWISE;
	if (Cross(a, b) < 0LL) return CLOCKWISE;
	if (Dot(a, b) < 0LL) return ONLINE_BACK; // p2 - p0 - p1
	if (Norm(a) < Norm(b)) return ONLINE_FRONT; // p0 - p1 - p2

	return ON_SEGMENT; // p0 - p2 - p1
}

bool Intersect(Point& p1, Point& p2, Point& p3, Point& p4) {
	return (CCW(p1, p2, p3) * CCW(p1, p2, p4) <= 0 && CCW(p3, p4, p1) * CCW(p3, p4, p2) <= 0);
	// 한 선분을 기준으로 다른 선분의 끝점이 각각 반시계 방향과 시계 방향에 있는 경우 교차 판정 가능.
}

Polygon GrahamScan(Polygon& s) {
	Polygon poly;
	if (s.size() < 3) return s; // 점이면 점, 직선이면 직선

	sort(begin(s), end(s));
	Point stdP(s[0].x, s[0].y);

	// 기준점 빼고 반시계 정렬
	sort(begin(s) + 1, end(s), [&stdP](const Point& p1, const Point& p2) {
		Point tempP1(p1.x - stdP.x, p1.y - stdP.y);
		Point tempP2(p2.x - stdP.x, p2.y - stdP.y);
		if (1LL * tempP1.y * tempP2.x != 1LL * tempP1.x * tempP2.y) return 1LL * tempP1.y * tempP2.x < 1LL * tempP1.x * tempP2.y; // 반시계일 때 true
		return p1.y != p2.y ? p1.y < p2.y : p1.x < p2.x;
		});

	poly.emplace_back(s[0].x, s[0].y);
	poly.emplace_back(s[1].x, s[1].y);

	int next{ 2 };
	int N = static_cast<int>(s.size());
	while (next < N) { // 모든 점 훑기
		// 스택에 2개 이상의 점이 남아 있는 한...
		while (poly.size() >= 2) {
			Point first = *(poly.end() - 1);
			Point second = *(poly.end() - 2);
			// 스택 최상단 점 2개와 다음 점의 관계가 CCW일 때까지 스택 pop
			if (CCW(second, first, s[next]) != CLOCKWISE) {
				break;
			}
			poly.pop_back();
		}
		// 다음 점을 스택에 넣기
		poly.emplace_back(s[next].x, s[next].y);
		++next;
	}
	// 직선인 경우 시작점 - 끝점 리턴
	return poly;
}

bool ChkAInB(Polygon& p1, Polygon& p2) {
	// p1가 B 내부인지 확인(선분 위인지도 확인)
	if (static_cast<int>(p2.size()) < 3) return false; // 내부인지 확인 불가능

	for (Point& p : p1) {
		int last{ -100 };
		for (int s{}, e{ static_cast<int>(p2.size()) }; s < e; ++s) {
			int tmp{CCW(p, p2[s], p2[(s + 1) % e])};
			if (tmp == ONLINE_BACK) {
				return true;
			}
			
			if (last == -100) last = tmp;
			else if (last != tmp) {
				// 결과가 다른 경우 내부에 있지 않음.
				return false;
			}
		}
	}
	return true; // 모든 점에 대해 CCW 결과 동일 => 내부에 존재
}

bool ChkACrossB(Polygon& p1, Polygon& p2) {
	// 선분끼리 겹치는지 확인
	if (static_cast<int>(p1.size()) < 2 || static_cast<int>(p2.size()) < 2) return false;
	for (int s1{}, e1{ static_cast<int>(p1.size()) }; s1 < e1; ++s1) {
		for (int s2{}, e2{ static_cast<int>(p2.size()) }; s2 < e2; ++s2) {
			if(Intersect(p1[s1], p1[(s1 + 1) % e1], p2[s2], p2[(s2 + 1) % e2])) {
				return true;
			}
		}
	}
	return false;
}

int main() {
	cout.tie(nullptr), cin.tie(nullptr), ios::sync_with_stdio(false);
	// freopen("D.in", "r", stdin);
	int T{}; cin >> T;
	//for (int tc{1};;++tc) {
	while (T--) {
		int n{}, m{}; cin >> n >> m; // 검정 점, 흰 점
		if (n == 0 && m == 0) break;
		// cout << tc << " : ";
		Polygon bps(n, Point(0, 0)), wps(m, Point(0, 0));
		for (Point& p : bps) cin >> p.x >> p.y;
		for (Point& p : wps) cin >> p.x >> p.y;

		Polygon pWhite(move(GrahamScan(wps)));
		Polygon pBlack(move(GrahamScan(bps)));

		// 내부인지 확인(선분 위인지도 확인)
		if (ChkAInB(pWhite, pBlack) || ChkAInB(pBlack, pWhite)) {
			cout << "NO\n";
			continue;
		}

		// 겹치는지 확인
		if (ChkACrossB(pWhite, pBlack)) {
			cout << "NO\n";
			continue;
		}

		// 2개 1개인 경우
		int pWhiteSiz{ static_cast<int>(pWhite.size()) }, pBlackSiz{ static_cast<int>(pBlack.size()) };
		if (pWhiteSiz == 2 && pBlackSiz == 1) {
			int tmp{ CCW(pBlack[0], pWhite[0], pWhite[1])};
			if (tmp == ONLINE_BACK || tmp == ONLINE_FRONT || tmp == ON_SEGMENT) {
				cout << "NO\n";
				continue;
			}
		}
		else if (pWhiteSiz == 1 && pBlackSiz == 2) {
			int tmp{ CCW(pWhite[0], pBlack[0], pBlack[1]) };
			if (tmp == ONLINE_BACK || tmp == ONLINE_FRONT || tmp == ON_SEGMENT) {
				cout << "NO\n";
				continue;
			}
		}

		cout << "YES\n";
	}
	return 0;
}