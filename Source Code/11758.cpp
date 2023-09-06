#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

struct Point {
	int x, y;
	Point(int x, int y) : x(x), y(y) {}
	Point() = default;

	bool operator==(const Point& other) const = default; // auto-generated
	Point operator+(const Point& other) const;
	Point operator-(const Point& other) const;
};
using Vector = Point;

Point Point::operator+(const Point& other) const
{
	return Point(this->x + other.x, this->y + other.y);
}
Point Point::operator-(const Point& other) const
{
	return Point(this->x - other.x, this->y - other.y);
}

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

int main() {
	cin.tie(nullptr), ios::sync_with_stdio(false);
	Point p1{}, p2{}, p3{}; // default constructor

	cin >> p1.x >> p1.y >> p2.x >> p2.y >> p3.x >> p3.y;

	int result = CCW(p1, p2, p3);
	if (result == ONLINE_FRONT || result == ONLINE_BACK) result = 0;
	cout << result << '\n';

	return 0;
}