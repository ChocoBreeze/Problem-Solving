#include <iostream>
#include <vector>
#include <limits> // to use epsilon
#include <algorithm>

using namespace std;

constinit const double EPS = numeric_limits<double>::epsilon(); // 2.2204460492503131e-016

struct Point {
	double x, y; // 실제 위치
	double p, q; // 기준점(보통의 첫점)으로부터의 상대 위치
	Point(double x, double y, double p = 1, double q = 0) : x(x), y(y), p(p), q(q) {}
};

double cross(const Point& p1, const Point& p2) {
	return p1.x * p2.y - p1.y * p2.x;
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	int N{}; cin >> N;

	vector<Point> points(N, Point(0,0));
	for (Point& p : points) {
		cin >> p.x >> p.y;
	}

	double sum{};
	Point standardP = points[0]; // 아무 점이나 잡고 해도 상관 없다.
	for (int i{ 1 }; i < N - 1; ++i) {
		Point p1(points[i].x - standardP.x, points[i].y - standardP.y);
		Point p2(points[i + 1].x - standardP.x, points[i + 1].y - standardP.y);
		sum += cross(p1, p2) / 2; // 평행사변형 넓이 합
	}
	if (sum < 0) sum = -sum;

	cout << fixed;//cout.fixed;
	cout.precision(1);
	cout << sum << '\n';

	return 0;
}