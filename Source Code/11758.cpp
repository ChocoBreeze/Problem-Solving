// 개념 참고. : https://coloredrabbit.tistory.com/162
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

double cross(Vector a, Vector b) { // 외적
	return a.x * b.y - a.y * b.x;
}

static const int ON_SEGMENT = 0;
static const int CLOCKWISE = -1;
static const int COUNTER_CLOCKWISE = 1;
int ccw(Point p0, Point p1, Point p2) {
	Vector a = p1 - p0;
	Vector b = p2 - p0;
	if (cross(a, b) > EPS) return -1; // 반시계
	if (cross(a, b) < -EPS) return 1; // 시계
	return 0;
}

int main() {
	cin.tie(NULL)->sync_with_stdio(false);
	double a, b, c, d, e, f;
	cin >> a >> b >> c >> d >> e >> f;
	Point p1(a,b), p2(c,d), p3(e,f);

	cout << ccw(p2, p1, p3);

	return 0;
}