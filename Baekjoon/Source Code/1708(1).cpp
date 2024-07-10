// ���� ������ �̷�� ���� ������ ���ϴ� ���α׷��� �ۼ�
// x��ǥ�� y��ǥ�� ������ ���� 40,000�� ���� �ʴ´�. -> int ���� �� ����
// �Է����� �־����� �ٰ����� ��� ���� �������� �̷�� ���� ����.
// Andrew's Scan

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct Point {
    int x, y;
    Point() = default;
    Point(int x, int y) : x(x), y(y) {}
    Point(const Point& other) : x(other.x), y(other.y) {}
    Point operator+(const Point& other) const;
    Point operator-(const Point& other) const;
    bool operator<(const Point& p) const { // x�� �켱���� x�� ������ y ��
        return x != p.x ? x < p.x : y < p.y;
    }
};
using Vector = Point;
using Polygon = vector<Point>;

Point Point::operator+(const Point& other) const
{
    return Point(this->x + other.x, this->y + other.y);
}
Point Point::operator-(const Point& other) const
{
    return Point(this->x - other.x, this->y - other.y);
}

long long Dot(const Vector& a, const Vector& b) {
    return 1LL * a.x * b.x + 1LL * a.y * b.y;
}
long long Cross(const Vector& a, const Vector& b) {
    return 1LL * a.x * b.y - 1LL * a.y * b.x;
}
long long Norm(const Vector& a) {
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
        for (int n{ static_cast<int>(u.size()) }; n >= 2 && CCW(u[n - 2], u[n - 1], s[i]) != CLOCKWISE; --n) {
            // �� ���� �ִ� ���� �������� �ʴ� ��� -> ���฻�� ��¥�� ������ ��ǥ�鸸 �ֱ�
            // for (int n = u.size(); n >= 2 && ccw(u[n - 2], u[n - 1], s[i]) != CLOCKWISE; --n) {
            // ���� ������ �� ���� �ִ� ���� �����ؾ� �ϴ� ��� -> ���������� ��� pop
            // for (int n = u.size(); n >= 2 && ccw(u[n - 2], u[n - 1], s[i]) == COUNTER_CLOCKWISE; --n) {
            u.pop_back();
        }
        u.emplace_back(s[i]);
    }

    // ���� ���� �Ʒ� �κ� �����
    for (int i{ static_cast<int>(s.size()) - 3 }; i >= 0; --i) {
        for (int n{ static_cast<int>(l.size()) }; n >= 2 && CCW(l[n - 2], l[n - 1], s[i]) != CLOCKWISE; --n) {
            // �� ���� �ִ� ���� �������� �ʴ� ��� -> ���฻�� ��¥�� ������ ��ǥ�鸸 �ֱ�
            // for (int n = l.size(); n >= 2 && ccw(l[n - 2], l[n - 1], s[i]) != CLOCKWISE; --n) {
            // ���� ������ �� ���� �ִ� ���� �����ؾ� �ϴ� ��� -> ���������� ��� pop
            // for (int n = l.size(); n >= 2 && ccw(l[n - 2], l[n - 1], s[i]) == COUNTER_CLOCKWISE; --n) {
            l.pop_back();
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

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int N{};
    cin >> N;
    Polygon points(N, Point(0,0));
    for (Point& p : points) {
        cin >> p.x >> p.y;
    }
    
    Polygon answer = AndrewScan(points);
    cout << answer.size() << '\n';

    return 0;
}