/*
Graham's Scan
���� ���� ���� �� �ٰ����� ���� ���ϱ�
�� �Ѹ����� 50m^2�� �� �� ����.
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using ll = long long;

struct Point {
	int x, y;
	Point(int x, int y) : x(x), y(y) {}
	Point(const Point& other) : x(other.x), y(other.y) {}
	Point operator-(const Point& other) const;
	bool operator<(const Point& other) const { // y�� �켱���� y�� ������ x ��
		return y != other.y ? y < other.y : x < other.x;
	}
};
using Vector = Point;
using Polygon = vector <Point>;

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

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	int N{}; cin >> N;
	vector<Point> points(N, Point(0,0));
	for (Point& p : points) {
		cin >> p.x >> p.y;
	}

	sort(begin(points), end(points)); // ���� ���� �Ʒ� �� ã�� ���ؼ� ����
	Point stdP(points[0].x, points[0].y); // ������

	auto compare = [&stdP](const Point& p1, const Point& p2) {
		Point tempP1(p1.x - stdP.x, p1.y - stdP.y);
		Point tempP2(p2.x - stdP.x, p2.y - stdP.y);
		if (1LL * tempP1.y * tempP2.x != 1LL * tempP1.x * tempP2.y) { // �ݽð��� �� true
			return 1LL * tempP1.y * tempP2.x < 1LL * tempP1.x * tempP2.y;
		}
		return p1.y != p2.y ? p1.y < p2.y : p1.x < p2.x; // ���� ũ�� ��
	};
	sort(begin(points) + 1, end(points), compare); // ���������� �ݽð� ���� ����

	// stack ��� vector ���
	vector<int> poly;
	poly.push_back(0);
	poly.push_back(1);

	int next{ 2 };
	N = static_cast<int>(points.size());
	while (next < N) { // ��� �� �ȱ�
		while (poly.size() >= 2) { // ���ÿ� 2�� �̻��� ���� ���� �ִ� ��
			int first = *(poly.end() - 1); // poly.back()
			int second = *(poly.end() - 2);
			// ���� �ֻ�� �� 2���� ���� ���� ���谡 CCW�� ������ ���� pop
			if (CCW(points[second], points[first], points[next]) == COUNTER_CLOCKWISE) {
				break;
			}
			poly.pop_back();
		}
		poly.push_back(next++); // ���� ���� ���ÿ� �ֱ�
	}

	ll sum{};
	stdP = points[poly[0]];
	N = static_cast<int>(poly.size());
	for (int i{ 1 }; i < N - 1; ++i) {
		// poly�� ��꿡 ����ؾ� �ϴµ�, �ٸ� �� �־���� ���� Ʋ���� ã�� �ֳ�..
		Vector v1 = points[poly[i]] - stdP;
		Vector v2 = points[poly[i + 1]] - stdP;
		sum += Cross(v1, v2) / 2; // ����纯�� ���� ��
	}
	if (sum < 0) sum = -sum;
	sum /= 50; // �� ������
	cout << sum << '\n';

	return 0;
}