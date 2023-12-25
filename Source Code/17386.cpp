#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

struct Point {
	int x, y;

	Point(int x, int y) : x(x), y(y) {}
	Point operator-(const Point& other) const;

	double norm() { return x * x + y * y; }
};
using Vector = Point;

Point Point::operator-(const Point& other) const
{
	return Point(this->x - other.x, this->y - other.y);
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

bool intersect(Point& p1, Point& p2, Point& p3, Point& p4) {
	return (CCW(p1, p2, p3) * CCW(p1, p2, p4) < 0 && CCW(p3, p4, p1) * CCW(p3, p4, p2) < 0);
	// 한 선분을 기준으로 다른 선분의 끝점이 각각 반시계 방향과 시계 방향에 있는 경우 교차 판정 가능.
	// 0을 미포함(끝 점이 선분이 닿는 경우 제외)해야 함
}

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int a, b, c, d;
	cin >> a >> b >> c >> d;
	Point L1s(a, b), L1e(c, d);
	cin >> a >> b >> c >> d;
	Point L2s(a, b), L2e(c, d);

	cout << intersect(L1s, L1e, L2s, L2e) << '\n';

	return 0;
}