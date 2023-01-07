#include <iostream>
#include <vector>
#include <limits>

using namespace std;

const double EPS = std::numeric_limits<double>::epsilon();

struct Point {
	double x, y;

	Point() {}
	Point(double x, double y) : x(x), y(y) {}
	Point operator-(Point p) { return Point(x - p.x, y - p.y); }

	double norm() { return x * x + y * y; }
};
using Vector = Point;
struct Segment {
	Point p1;
	Point p2;
	Segment() {}
	Segment(Point p1, Point p2) : p1(p1), p2(p2) {}
};

double dot(Vector a, Vector b) { // 내적
	return a.x * b.x + a.y * b.y;
}

double cross(Vector a, Vector b) { // 외적
	return a.x * b.y - a.y * b.x;
}

static const int ON_SEGMENT = 0;
static const int ONLINE_FRONT = -2;
static const int ONLINE_BACK = 2;
static const int CLOCKWISE = -1;
static const int COUNTER_CLOCKWISE = 1;
int ccw(Point p0, Point p1, Point p2) {
	Vector a = p1 - p0;
	Vector b = p2 - p0;
	if (cross(a, b) > EPS) return COUNTER_CLOCKWISE; // 반시계
	if (cross(a, b) < -EPS) return CLOCKWISE; // 시계
	if (dot(a, b) < -EPS) return ONLINE_BACK; // p2 - p0 - p1 순
	if (a.norm() < b.norm()) return ONLINE_FRONT; // p0 - p1 - p2 순

	return ON_SEGMENT; // p0 - p2 - p1 순
}


bool intersect(Point& p1, Point& p2, Point& p3, Point& p4) {
	return (ccw(p1, p2, p3) * ccw(p1, p2, p4) <= 0 && ccw(p3, p4, p1) * ccw(p3, p4, p2) <= 0);
	// 한 선분을 기준으로 다른 선분의 끝점이 각각 반시계 방향과 시계 방향에 있는 경우 교차 판정 가능.
	// 0을 포함(끝 점이 선분이 닿는 경우)해야 함
}

int main() {
	cin.tie(NULL)->sync_with_stdio(false);
	double a, b, c, d;
	cin >> a >> b >> c >> d;
	Point L1s(a, b), L1e(c, d);
	cin >> a >> b >> c >> d;
	Point L2s(a, b), L2e(c, d);

	cout << intersect(L1s, L1e, L2s, L2e);

	return 0;
}