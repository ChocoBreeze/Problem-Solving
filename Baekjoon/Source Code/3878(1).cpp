// Graham Scan
// 첫 의도 - 모든 경우 확인
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
			if (CCW(second, first, s[next]) == COUNTER_CLOCKWISE) {
				break;
			}
			poly.pop_back();
		}
		// 다음 점을 스택에 넣기
		poly.emplace_back(s[next].x, s[next].y);
		++next;
	}


	// if (static_cast<int>(poly.size()) < 3) return Polygon(); // 추가 - empty vector

	// 직선인 경우 시작점 - 끝점 리턴
	return poly;
}

bool ChkPointAndSegment(Point& p1, Point& p2, Point& p3) {
	// 선분 p2p3 위에 p1이 있을 때
	if (CCW(p1, p2, p3) == ONLINE_BACK) return true;
	return false;
}

bool ChkSegmentAndSegment(Point& p1, Point& p2, Point& p3, Point& p4) {
	// 선분 p1p2, 선분 p3p4 교차 판정
	if (Intersect(p1, p2, p3, p4)) return true;
	return false;
}

bool ChkPointAndPolygon(Point& p1, Polygon& p) {
	int last{ -100 };
	bool contain{ true };
	for (int s{}, e{ static_cast<int>(p.size()) }; s < e; ++s) {
		int ret{ CCW(p1, p[s], p[(s + 1) % e]) };
		if (ret == ON_SEGMENT || ret == ONLINE_FRONT || ret == ONLINE_BACK) {
			return true; // 위의 점임
		}
		if (last == -100) last = ret;
		else if (last != ret) {
			contain = false;
			break;
		}
	}
	if (contain) { // 내부의 점
		return true;
	}
	return false;
}

bool ChkSegmentAndPolygon(Point& p1, Point& p2, Polygon& p) {
	// 선분 p1p2와 Polygon p 판정.

	// 선분 p1p2와 p가 만나기.
	for (int s{}, e{ static_cast<int>(p.size()) }; s < e; ++s) {
		if (Intersect(p1, p2, p[s], p[(s + 1) % e])) {
			return true;
		}
	}

	// p1, p2가 모두 p 내부일 때
	auto chkInternal = [](Point& p1, Polygon& p) -> bool {
		int last{ -100 };
		bool contain{ true };
		for (int s{}, e{ static_cast<int>(p.size()) }; s < e; ++s) {
			int ret{ CCW(p1, p[s], p[(s + 1) % e]) };
			if (ret == ON_SEGMENT || ret == ONLINE_FRONT || ret == ONLINE_BACK) {
				return false; // 위의 점임
			}
			if (last == -100) last = ret;
			else if (last != ret) {
				contain = false;
				break;
			}
		}
		if (contain) { // 내부의 점
			return true;
		}
		return false;
		};
	if (chkInternal(p1, p) && chkInternal(p2, p)) {
		return true;
	}
	return false;
}

int main() {
	cout.tie(nullptr), cin.tie(nullptr), ios::sync_with_stdio(false);
	int T{}; cin >> T;
	while (T--) {
		int n{}, m{}; cin >> n >> m; // 검정 점, 흰 점
		Polygon bps(n, Point(0, 0)), wps(m, Point(0, 0));
		for (Point& p : bps) cin >> p.x >> p.y;
		for (Point& p : wps) cin >> p.x >> p.y;

		if (n == 1) {
			if (m == 1) cout << "YES\n";
			else if (m == 2) {
				if (ChkPointAndSegment(bps[0], wps[0], wps[1])) cout << "NO\n";
				else cout << "YES\n";
			}
			else { // m >= 3
				Polygon pWhite(move(GrahamScan(wps)));
				if (static_cast<int>(pWhite.size()) < 3) {
					// 점 - 선분 교차
					if (ChkPointAndSegment(bps[0], pWhite[0], pWhite[1])) cout << "NO\n";
					else cout << "YES\n";
				}
				else {
					// 점 포함 여부확인
					if (ChkPointAndPolygon(bps[0], pWhite)) cout << "NO\n";
					else cout << "YES\n";
				}
			}
		}
		else if (m == 1) {
			if (n == 2) {
				if (ChkPointAndSegment(wps[0], bps[0], bps[1])) cout << "NO\n";
				else cout << "YES\n";
			}
			else { // n >= 3
				Polygon pBlack(move(GrahamScan(bps)));
				if (static_cast<int>(pBlack.size()) < 3) {
					// 점 - 선분 교차
					if (ChkPointAndSegment(wps[0], pBlack[0], pBlack[1])) cout << "NO\n";
					else cout << "YES\n";
				}
				else {
					// 점 포함 여부확인
					if (ChkPointAndPolygon(wps[0], pBlack)) cout << "NO\n";
					else cout << "YES\n";
				}
			}
		}
		else if (n == 2) {
			if (m == 2) {
				// 선분 교차 여부(끝에서 만나도 X)
				if (ChkSegmentAndSegment(wps[0], wps[1], bps[0], bps[1])) cout << "NO\n";
				else cout << "YES\n";
			}
			else if (m >= 3) {
				Polygon pWhite(move(GrahamScan(wps)));
				if (static_cast<int>(pWhite.size()) < 3) {
					// 선분 - 선분 교차
					if (ChkSegmentAndSegment(bps[0], bps[1], pWhite[0], pWhite[1])) cout << "NO\n";
					else cout << "YES\n";
				}
				else {
					// 선분 - convex hull
					if (ChkSegmentAndPolygon(bps[0], bps[1], pWhite)) cout << "NO\n";
					else cout << "YES\n";
				}
			}
		}
		else if (m == 2) {
			// n >= 3
			Polygon pBlack(move(GrahamScan(bps)));
			if (static_cast<int>(pBlack.size()) < 3) {
				// 선분 - 선분 교차
				if (ChkSegmentAndSegment(wps[0], wps[1], pBlack[0], pBlack[1])) cout << "NO\n";
				else cout << "YES\n";
			}
			else {
				// 선분 - convex hull
				if (ChkSegmentAndPolygon(wps[0], wps[1], pBlack)) cout << "NO\n";
				else cout << "YES\n";
			}
		}
		else { // n >= 3 && m >= 3
			Polygon pWhite(move(GrahamScan(wps)));
			Polygon pBlack(move(GrahamScan(bps)));
			if (static_cast<int>(pBlack.size()) < 3) {
				if (static_cast<int>(pWhite.size()) < 3) {
					// 선분 - 선분 교차
				}
				else { // wps만 convex hull 구성 가능
					// 선분 - convex hull
					if (ChkSegmentAndPolygon(pBlack[0], pBlack[1], pWhite)) cout << "NO\n";
					else cout << "YES\n";
				}
			}
			else if (static_cast<int>(pWhite.size()) < 3) { // bps만 convex hull 구성 가능
				// 선분 - convex hull
				if (ChkSegmentAndPolygon(pWhite[0], pWhite[1], pBlack)) cout << "NO\n";
				else cout << "YES\n";
			}
			else { // 둘 다 convex hull 구성 가능.
				bool chk{ true };

				// 검은색 점이 모두 pWhite 내부인지 확인
				[&]() -> void {
					for (auto& p : bps) { // 검은색 점마다
						bool contain{ true };
						int last{ -100 };
						for (int s{}, e{ static_cast<int>(pWhite.size()) }; s < e; ++s) { // white polygon
							int ret{ CCW(p, pWhite[s], pWhite[(s + 1) % e]) };
							if (ret == ONLINE_BACK) {
								chk = false; // 가를 수 없음.
								return;
							}
							if (last == -100) last = ret;
							else if (last != ret) {
								contain = false;
								break;
							}
						}
						if (contain) { // 내부의 점인 경우 CCW 결과가 모두 동일
							chk = false; // 가를 수 없음.
							return;
						}
					}
					} ();

					// 흰색 점이 모두 pBlack 내부인지 확인
					if (chk) {
						[&]() -> void {
							for (auto& p : wps) { // 흰색 점마다
								bool contain{ true };
								int last{ -100 };
								for (int s{}, e{ static_cast<int>(pBlack.size()) }; s < e; ++s) { // white polygon
									int ret{ CCW(p, pBlack[s], pBlack[(s + 1) % e]) };
									if (ret == ONLINE_BACK) {
										chk = false; // 가를 수 없음.
										return;
									}
									if (last == -100) last = ret;
									else if (last != ret) {
										contain = false;
										break;
									}
								}
								if (contain) { // 내부의 점인 경우 CCW 결과가 모두 동일
									chk = false; // 가를 수 없음.
									return;
								}
							}
							} ();
					}

					// 선분끼리 교차 확인
					if (chk) {
						[&]() {
							for (int ws{}, we{ static_cast<int>(pWhite.size()) }; ws < we; ++ws) {
								for (int bs{}, be{ static_cast<int>(pBlack.size()) }; bs < be; ++bs) {
									if (ChkSegmentAndSegment(pWhite[ws], pWhite[(ws + 1) % we], pBlack[bs], pBlack[(bs + 1) % be])) {
										chk = false;
										return;
									}
								}
							}
							} ();
					}

					if (chk) cout << "YES\n";
					else cout << "NO\n";
			}
		}
	}
	return 0;
}