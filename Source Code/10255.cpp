// 계산 기하학 공부
#include <iostream>
#include <limits>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;
constinit const double EPS = numeric_limits<double>::epsilon();

struct Point {
	int x, y;
	Point(int x, int y) : x(x), y(y) {}
	Point operator-(const Point& other) const {
		return Point(this->x - other.x, this->y - other.y);
	}
	Point operator+(const Point& other) const {
		return Point(this->x + other.x, this->y + other.y);
	}
	bool operator==(const Point& other) const {
		return (this->x == other.x && this->y == other.y);
	}
};
using Vector = Point;

struct Segment {
	Point p1, p2;
	Segment(Point p1, Point p2) : p1(p1.x, p1.y), p2(p2.x, p2.y) {}
};
using Line = Segment;

int dot(const Vector& a, const Vector& b){
	return a.x * b.x + a.y * b.y;
}

int cross(const Vector& a, const Vector& b) {
	return a.x * b.y - b.x * a.y;
}

int abs(const Vector& a) {
	return static_cast<int>(sqrt(a.x * a.x + a.y * a.y));
}

int norm(const Vector& a) {
	return a.x * a.x + a.y * a.y;
}

int getDistanceLP(const Line& l, const Point& p) {
	double ret = abs(static_cast<double>(cross(l.p2 - l.p1, p - l.p1)) / abs(l.p2 - l.p1));
	if (ret < EPS) return 0;
	return 1; // 교차 안 하는 경우라서 0만 아닌 값으로
}

int getDistanceSP(const Segment& s, const Point& p) {
	if (dot(s.p2 - s.p1, p - s.p1) < 0.0) return abs(p - s.p1);
	if (dot(s.p1 - s.p2, p - s.p2) < 0.0) return abs(p - s.p2);
	return getDistanceLP(s, p);
}

constinit const int ON_SEGMENT = 0;
constinit const int ONLINE_FRONT = -2;
constinit const int ONLINE_BACK = 2;
constinit const int CLOCKWISE = -1;
constinit const int COUNTER_CLOCKWISE = 1;
int ccw(Point p0, Point p1, Point p2) {
	Vector a = p1 - p0;
	Vector b = p2 - p0;
	if (cross(a, b) > 0) return COUNTER_CLOCKWISE;
	if (cross(a, b) < 0) return CLOCKWISE;
	if (dot(a, b) < 0) return ONLINE_BACK; // p2 - p0 - p1
	if (norm(a) < norm(b)) return ONLINE_FRONT; // p0 - p1 - p2

	return ON_SEGMENT; // p0 - p2 - p1
}

bool intersect(Point p1, Point p2, Point p3, Point p4) {
	return(ccw(p1, p2, p3) * ccw(p1, p2, p4) <= 0 &&
		ccw(p3, p4, p1) * ccw(p3, p4, p2) <= 0);
}
bool intersect(Segment s1, Segment s2) {
	return intersect(s1.p1, s1.p2, s2.p1, s2.p2);
}

bool ChkSamePart(Segment one, Segment another) {
	bool ret{ true };
	if (one.p1 == another.p2) {
		if (dot(one.p2 - one.p1, another.p1 - another.p2) < 0) ret = false;
	}
	else if (one.p1 == another.p1) {
		if (dot(one.p2 - one.p1, another.p2 - another.p1) < 0) ret = false;
	}
	else if (one.p2 == another.p2) {
		if (dot(one.p1 - one.p2, another.p1 - another.p2) < 0) ret = false;
	}
	else if (one.p2 == another.p1) {
		if (dot(one.p1 - one.p2, another.p2 - another.p1) < 0) ret = false;
	}
	return ret;
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);

	int T{}; cin >> T;
	while (T--) {
		int xmin, ymin, xmax, ymax; cin >> xmin >> ymin >> xmax >> ymax;
		Point p1(xmin, ymin), p2(xmax, ymin), p3(xmin, ymax), p4(xmax, ymax);
		Segment s1(p1, p2), s2(p1, p3), s3(p2, p4), s4(p3, p4);
		int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
		Segment s(Point(x1, y1), Point(x2, y2));

		int cnt{};
		bool chk1{ false }, chk2{ false }, chk3{ false }, chk4{ false };
		if (intersect(s, s1)) { ++cnt; chk1 = true; }
		if (intersect(s, s2)) { ++cnt; chk2 = true; }
		if (intersect(s, s3)) { ++cnt; chk3 = true; }
		if (intersect(s, s4)) { ++cnt; chk4 = true; }

		bool chkInf{ false };
		if (chk1 && cross(s.p1 - s.p2, s1.p1 - s1.p2) == 0 && ChkSamePart(s, s1)) { cnt = 4; chkInf = true; }
		else if (chk2 && cross(s.p1 - s.p2, s2.p1 - s2.p2) == 0 && ChkSamePart(s, s2)) { cnt = 4; chkInf = true; }
		else if (chk3 && cross(s.p1 - s.p2, s3.p1 - s3.p2) == 0 && ChkSamePart(s, s3)) { cnt = 4; chkInf = true; }
		else if (chk4 && cross(s.p1 - s.p2, s4.p1 - s4.p2) == 0 && ChkSamePart(s, s4)) { cnt = 4; chkInf = true; }
		
		if (!chkInf) {
			if (getDistanceSP(s, p1) == 0) --cnt;
			if (getDistanceSP(s, p2) == 0) --cnt;
			if (getDistanceSP(s, p3) == 0) --cnt;
			if (getDistanceSP(s, p4) == 0) --cnt;
		}

		cout << cnt << '\n';
	}
	
	return 0;
}