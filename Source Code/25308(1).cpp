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
	bool operator<(const Point& p) const { // x를 우선으로 x가 같으면 y 비교
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
    // x가 작은 것부터 2개를 u에 추가
    u.emplace_back(s[0]);
    u.emplace_back(s[1]);

    // x가 큰 것부터 2개를 l에 추가
    int last = static_cast<int>(s.size());
    l.emplace_back(s[last - 1]);
    l.emplace_back(s[last - 2]);

    // 볼록 껍질 윗 부분 만들기
    for (int i{ 2 }; i < last; ++i) {
        for (int n{ static_cast<int>(u.size()) }; n >= 2 && CCW(u[n - 2], u[n - 1], s[i]) == COUNTER_CLOCKWISE; --n) {
            u.pop_back(); // 평행인 점 포함(오목해지는 경우 pop)
        }
        u.emplace_back(s[i]);
    }

    // 볼록 껍질 아랫 부분 만들기
    for (int i{ static_cast<int>(s.size()) - 3 }; i >= 0; --i) {
        for (int n{ static_cast<int>(l.size()) }; n >= 2 && CCW(l[n - 2], l[n - 1], s[i]) == COUNTER_CLOCKWISE; --n) {
            l.pop_back(); // 평행인 점 포함(오목해지는 경우 pop)
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