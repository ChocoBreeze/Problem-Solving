// 볼록 껍질을 이루는 점의 개수를 구하는 프로그램을 작성
// x좌표와 y좌표의 범위는 절댓값 40,000을 넘지 않는다. -> int 곱셈 시 주의
// 입력으로 주어지는 다각형의 모든 점이 일직선을 이루는 경우는 없다.
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
    bool operator<(const Point& p) const { // x를 우선으로 x가 같으면 y 비교
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
    // x가 작은 것부터 2개를 u에 추가
    u.emplace_back(s[0]);
    u.emplace_back(s[1]);

    // x가 큰 것부터 2개를 l에 추가
    int last = static_cast<int>(s.size());
    l.emplace_back(s[last - 1]);
    l.emplace_back(s[last - 2]);

    // 볼록 껍질 윗 부분 만들기
    for (int i{ 2 }; i < last; ++i) {
        for (int n{ static_cast<int>(u.size()) }; n >= 2 && CCW(u[n - 2], u[n - 1], s[i]) != CLOCKWISE; --n) {
            // 변 위에 있는 점을 포함하지 않는 경우 -> 평행말고 진짜로 볼록인 좌표들만 넣기
            // for (int n = u.size(); n >= 2 && ccw(u[n - 2], u[n - 1], s[i]) != CLOCKWISE; --n) {
            // 볼록 껍질의 변 위에 있는 점도 포함해야 하는 경우 -> 오목해지는 경우 pop
            // for (int n = u.size(); n >= 2 && ccw(u[n - 2], u[n - 1], s[i]) == COUNTER_CLOCKWISE; --n) {
            u.pop_back();
        }
        u.emplace_back(s[i]);
    }

    // 볼록 껍질 아랫 부분 만들기
    for (int i{ static_cast<int>(s.size()) - 3 }; i >= 0; --i) {
        for (int n{ static_cast<int>(l.size()) }; n >= 2 && CCW(l[n - 2], l[n - 1], s[i]) != CLOCKWISE; --n) {
            // 변 위에 있는 점을 포함하지 않는 경우 -> 평행말고 진짜로 볼록인 좌표들만 넣기
            // for (int n = l.size(); n >= 2 && ccw(l[n - 2], l[n - 1], s[i]) != CLOCKWISE; --n) {
            // 볼록 껍질의 변 위에 있는 점도 포함해야 하는 경우 -> 오목해지는 경우 pop
            // for (int n = l.size(); n >= 2 && ccw(l[n - 2], l[n - 1], s[i]) == COUNTER_CLOCKWISE; --n) {
            l.pop_back();
        }
        l.emplace_back(s[i]);
    }

    // 시계 방향에 있을 수 있게 볼록 껍질 점 배열 생성
    // 왜 시작 인덱스가 u.size() - 2 인가? => 마지막 하나의 원소는 이미 l에 포함되어 있기 때문
    // 왜 i를 1까지 하는가? => 마찬가지로 시작 원소 또한 이미 l에 포함되어 있기 때문
    reverse(begin(l), end(l));
    for (int i{ static_cast<int>(u.size()) - 2 }; i >= 1; --i) { // 왜 u.size() - 2 부터 시작이지?
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