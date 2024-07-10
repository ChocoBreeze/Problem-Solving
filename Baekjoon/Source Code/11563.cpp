// 두 선분 사이 최단 거리
// 2000 * 2000 = 4'000'000
// 다 확인해도 충분함.

// 계산 기하학 공부
#include <iostream>
#include <limits>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;
// constinit const int EPS = DBL_EPSILON; - 아래 꺼 쓰거나 위에 꺼 쓰거나.
constinit const double EPS = numeric_limits<double>::epsilon();
// constinit const int INF = 1 << 30;
constinit const double INF = numeric_limits<double>::max();

struct Point {
	double x, y;
	Point(double x, double y) : x(x), y(y) {}
	Point operator- (const Point& other) const {
		return Point(this->x - other.x, this->y - other.y);
	}
	double norm() const {
		return x * x + y * y;
	}
	double abs() const {
		return sqrt(norm());
	}
};
using Vector = Point;

struct Segment {
	Point p1, p2;
	Segment(Point p1, Point p2) : p1(p1.x, p1.y), p2(p2.x, p2.y) {}
};
using Line = Segment;

double dot(const Vector& a, const Vector& b) { // 내적
	return a.x * b.x + a.y * b.y;
}

double cross(const Vector& a, const Vector& b) { // 외적
	return a.x * b.y - a.y * b.x;
}

constinit const int ON_SEGMENT = 0;
constinit const int ONLINE_FRONT = -2;
constinit const int ONLINE_BACK = 2;
constinit const int CLOCKWISE = -1;
constinit const int COUNTER_CLOCKWISE = 1;
int ccw(Point p0, Point p1, Point p2) {
	Vector a = p1 - p0;
	Vector b = p2 - p0;
	if (cross(a, b) > EPS) return COUNTER_CLOCKWISE;
	if (cross(a, b) < -EPS) return CLOCKWISE;
	if (dot(a, b) < -EPS) return ONLINE_BACK; // p2 - p0 - p1
	if (a.norm() < b.norm()) return ONLINE_FRONT; // p0 - p1 - p2

	return ON_SEGMENT; // p0 - p2 - p1
}

bool intersect(Point p1, Point p2, Point p3, Point p4) {
	// 반대 방향일 때
	return(ccw(p1, p2, p3) * ccw(p1, p2, p4) <= 0 && ccw(p3, p4, p1) * ccw(p3, p4, p2) <= 0);
}
bool intersect(const Segment& s1, const Segment& s2) {
	return intersect(s1.p1, s1.p2, s2.p1, s2.p2);
}

double abs(Vector&& p) { // && 해야 right value 받을 수 있음.
	return sqrt(p.norm());
}

double getDistanceLP(Line l, Point p) {
	return abs(cross(l.p2 - l.p1, p - l.p1) / abs(l.p2 - l.p1)); // line 위에 p
}

double getDistanceSP(Segment s, Point p) {
	if (dot(s.p2 - s.p1, p - s.p1) < 0.0) return abs(p - s.p1);
	if (dot(s.p1 - s.p2, p - s.p2) < 0.0) return abs(p - s.p2);
	return getDistanceLP(s, p);
}

double getDistance(Segment s1, Segment s2) {
	if (intersect(s1, s2)) return 0.0;
	return min(min(getDistanceSP(s1, s2.p1), getDistanceSP(s1, s2.p2)),
		min(getDistanceSP(s2, s1.p1), getDistanceSP(s2, s1.p2)));
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);

	int n{}, m{}; cin >> n >> m;
	vector<Segment> streetSinchon(n, Segment(Point(0, 0), Point(0, 0)));
	vector<Segment> streetAnam(m, Segment(Point(0, 0), Point(0, 0)));
	for (Segment& s : streetSinchon) {
		cin >> s.p1.x >> s.p1.y >> s.p2.x >> s.p2.y;
	}
	for (Segment& s : streetAnam) {
		cin >> s.p1.x >> s.p1.y >> s.p2.x >> s.p2.y;
	}

	double answer{ INF };
	cout << fixed;
	cout.precision(10);
	for (Segment& s1 : streetSinchon) {
		for (Segment& s2 : streetAnam) {
			answer = min(answer, getDistance(s1, s2));
		}
	}
	cout << answer << '\n';
	return 0;
}