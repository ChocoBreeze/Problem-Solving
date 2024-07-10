// Andrew's Scan
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;
constinit const int SIZE = 8;
// constinit const double rootTwo = sqrt(2);
// constexpr since C++26
const double rootTwo = sqrt(2);

struct Point {
	double x, y;
	Point(double x, double y) : x(x), y(y) {}
	Point operator-(const Point& other) const;
	bool operator<(const Point& p) const { // x�� �켱���� x�� ������ y ��
		return y != p.y ? y < p.y : x < p.x;
	}
};
using Vector = Point;
using Polygon = vector<Point>;
Point Point::operator-(const Point& other) const
{
	return Point(this->x - other.x, this->y - other.y);
}

double Dot(const Vector& v1, const Vector& v2) {
	return v1.x * v2.x + v1.y * v2.y;
}
double Cross(const Vector& v1, const Vector& v2) {
	return v1.x * v2.y - v1.y * v2.x;
}
double Norm(const Vector& v) {
	return v.x * v.x + v.y * v.y;
}

constinit const int ON_SEGMENT = 0;
constinit const int CLOCKWISE = -1;
constinit const int COUNTER_CLOCKWISE = 1;
constinit const int ONLINE_FRONT = -2;
constinit const int ONLINE_BACK = 2;
int CCW(const Point& p0, const Point& p1, const Point& p2) {
	Vector a = p1 - p0;
	Vector b = p2 - p0;
	if (Cross(a, b) > 0) return COUNTER_CLOCKWISE;
	if (Cross(a, b) < 0) return CLOCKWISE;
	if (Dot(a, b) < 0) return ONLINE_BACK; // p2 - p0 - p1
	if (Norm(a) < Norm(b)) return ONLINE_FRONT; // p0 - p1 - p2

	return ON_SEGMENT; // p0 - p2 - p1
}

Polygon AndrewScan(Polygon& s) {
    Polygon u, l;
    if (s.size() < 3) return s;

    sort(begin(s), end(s));
    // x�� ���� �ͺ��� 2���� u�� �߰�
    u.emplace_back(s[0]);
    u.emplace_back(s[1]);

    // x�� ū �ͺ��� 2���� l�� �߰�
    int last = static_cast<int>(s.size());
    l.emplace_back(s[last - 1]);
    l.emplace_back(s[last - 2]);

    // ���� ���� �� �κ� �����
    for (int i{ 2 }; i < last; ++i) {
        for (int n{ static_cast<int>(u.size()) }; n >= 2 && CCW(u[n - 2], u[n - 1], s[i]) == COUNTER_CLOCKWISE; --n) {
            u.pop_back(); // ������ �� ����(���������� ��� pop)
        }
        u.emplace_back(s[i]);
    }

    // ���� ���� �Ʒ� �κ� �����
    for (int i{ static_cast<int>(s.size()) - 3 }; i >= 0; --i) {
        for (int n{ static_cast<int>(l.size()) }; n >= 2 && CCW(l[n - 2], l[n - 1], s[i]) == COUNTER_CLOCKWISE; --n) {
            l.pop_back(); // ������ �� ����(���������� ��� pop)
        }
        l.emplace_back(s[i]);
    }

    // �ð� ���⿡ ���� �� �ְ� ���� ���� �� �迭 ����
    // �� ���� �ε����� u.size() - 2 �ΰ�? => ������ �ϳ��� ���Ҵ� �̹� l�� ���ԵǾ� �ֱ� ����
    // �� i�� 1���� �ϴ°�? => ���������� ���� ���� ���� �̹� l�� ���ԵǾ� �ֱ� ����
    reverse(begin(l), end(l));
    for (int i{ static_cast<int>(u.size()) - 2 }; i >= 1; --i) { // �� u.size() - 2 ���� ��������?
        l.emplace_back(u[i]);
    }
    return l;
}

using pdd = pair<double, double>;
vector<pdd> makePoints{
	{1,0},{1 / rootTwo, 1 / rootTwo},{0,1},{-1 / rootTwo,1 / rootTwo},
	{-1,0},{-1 / rootTwo,-1 / rootTwo},{0,-1},{1 / rootTwo,-1 / rootTwo}
};

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	vector<int> lengths(SIZE, 0);
	for (int& l : lengths) cin >> l;

	vector<int> indeces{ 0,1,2,3,4,5,6,7 };

	int answer{};
	do {
		Polygon points(SIZE, Point(0, 0));
		for (int i{}; i < SIZE; ++i) {
			points[i].x = lengths[indeces[i]] * makePoints[i].first;
			points[i].y = lengths[indeces[i]] * makePoints[i].second;
		}

		Polygon poly(move(AndrewScan(points)));
		if (poly.size() == SIZE) ++answer;
	} while (next_permutation(begin(indeces), end(indeces)));

	cout << answer << '\n';
	return 0;
}