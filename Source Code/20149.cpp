#include <iostream>
#include <vector>
#include <cmath>
#include <concepts>
#include <compare>

using namespace std;
using ll = long long;

struct Point {
	int x, y;

	Point(int x, int y) : x(x), y(y) {}
	Point operator-(const Point& other) const;
	Point operator+(const Point& other) const;
	template<typename T> requires std::floating_point<T> Point operator*(T& times) const;
	bool operator==(const Point& other) const = default;

	double norm() { return x * x + y * y; }
};
using Vector = Point;

Point Point::operator-(const Point& other) const {
	return Point(this->x - other.x, this->y - other.y);
}
Point Point::operator+(const Point& other) const {
	return Point(this->x + other.x, this->y + other.y);
}

template<typename T> requires std::floating_point<T>
Point Point::operator*(T& times) const {
	return Point(this->x * times, this->y * times);
}

struct Segment {
	Point p1, p2;
	Segment(Point p1, Point p2) : p1(p1), p2(p2) {}
};

ll Dot(const Vector& a, const Vector& b) {
	return 1LL * a.x * b.x + 1LL * a.y * b.y;
}
ll Cross(const Vector& a, const Vector& b) {
	return 1LL * a.x * b.y - 1LL * a.y * b.x;
}
ll Norm(const Vector& a) {
	return 1LL * a.x * a.x + 1LL * a.y * a.y;
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

bool Intersect(const Segment& s1, const Segment& s2) {
	const Point& p1{ s1.p1 }, & p2{ s1.p2 }, & p3{ s2.p1 }, & p4{ s2.p2 };

	return (CCW(p1, p2, p3) * CCW(p1, p2, p4) <= 0 && CCW(p3, p4, p1) * CCW(p3, p4, p2) <= 0);
	// 한 선분을 기준으로 다른 선분의 끝점이 각각 반시계 방향과 시계 방향에 있는 경우 교차 판정 가능.
	// 0을 포함(끝 점이 선분이 닿는 경우)해야 함
}

bool CheckVectorDirection(const Vector& v1, const Vector& v2) {
	return static_cast<double>(v1.x) / v1.y == static_cast<double>(v2.x) / v2.y;
}

bool CheckOneCross(const Segment& s1, const Segment& s2) {
	const Point& p1{ s1.p1 }, & p2{ s1.p2 }, & p3{ s2.p1 }, & p4{ s2.p2 };
	Vector a = p2 - p1;
	Vector b = p4 - p3, bRev = p3 - p4;

	if (CheckVectorDirection(a,b) || CheckVectorDirection(a,bRev)) { // 방향 일치 여부 
		if ((p1 == p3 && p2 == p4) || (p1 == p4 && p2 == p3)) return false; // 일치
		else if ((CCW(p1, p3, p2) == ONLINE_FRONT && CheckVectorDirection(p3 - p1, p2 - p3)) ||
			(CCW(p1, p4, p2) == ONLINE_FRONT && CheckVectorDirection(p4 - p1, p2 - p4)) ||
			(CCW(p2, p4, p1) == ONLINE_FRONT && CheckVectorDirection(p4 - p2, p1 - p4)) ||
			(CCW(p2, p3, p1) == ONLINE_FRONT && CheckVectorDirection(p3 - p2, p1 - p3)) ||
			(CCW(p1, p3, p2) == ONLINE_FRONT && CCW(p1, p4, p2) == ONLINE_FRONT) ||
			(CCW(p3, p1, p4) == ONLINE_FRONT && CCW(p3, p2, p4) == ONLINE_FRONT)) return false; // 일부 일치
		else return true; // 한점에서만 일치
	}
	return true; // 중간에서 교점 생김(cross)
}

void getCrossPoint(const Segment& s1, const Segment& s2) {
	Vector base = s2.p2 - s2.p1;
	ll d1 = Cross(base, s1.p1 - s2.p1); // s1.p1에서 s2까지 거리
	if (d1 < 0) d1 = -d1;
	ll d2 = Cross(base, s1.p2 - s2.p1); // s1.p2에서 s2까지 거리
	if (d2 < 0) d2 = -d2;
	double t = static_cast<double>(d1) / (d1 + d2); // d1 : d2 = t : 1 - t
	// return make_pair(s1.p1.x + (s1.p2.x - s1.p1.x) * t, s1.p1.y + (s1.p2.y - s1.p1.y) * t);
	cout << s1.p1.x + (s1.p2.x - s1.p1.x) * t << ' ' << s1.p1.y + (s1.p2.y - s1.p1.y) * t << '\n';
	// return s1.p1 + (s1.p2 - s1.p1) * t; // x 위치
}

void PrintPoint(const Point& p) {
	cout << p.x << ' ' << p.y << '\n';
}

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int a, b, c, d;
	cin >> a >> b >> c >> d;
	Point L1s(a, b), L1e(c, d);
	cin >> a >> b >> c >> d;
	Point L2s(a, b), L2e(c, d);

	Segment s1(L1s, L1e), s2(L2s, L2e);

	auto isCross = Intersect(s1, s2);
	cout << isCross << '\n';
	cout << fixed;
	cout.precision(12);
	// 한 점에서 교차하지 않는 경우에는 둘째 줄을 출력하지 않는다.
	if (isCross) {
		if (CheckOneCross(s1, s2)) { // 한점 교차
			if (s2.p1 == s1.p2) PrintPoint(s1.p2);
			else if (s2.p2 == s1.p2) PrintPoint(s2.p2);
			else if (s2.p2 == s1.p1) PrintPoint(s1.p1);
			else if (s2.p1 == s1.p1) PrintPoint(s2.p1);
			else getCrossPoint(s1, s2);
		}
	}
	
	return 0;
}