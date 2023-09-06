/*
Andrew's Scan
볼록 껍질 구한 후 다각형의 넓이 구하기
소 한마리가 50m^2에 살 수 있음.
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
	bool operator<(const Point& other) const { // y를 우선으로 y가 같으면 x 비교
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
			u.pop_back();
		}
		u.emplace_back(s[i]);
	}

	// 볼록 껍질 아랫 부분 만들기
	for (int i{ static_cast<int>(s.size()) - 3 }; i >= 0; --i) {
		for (int n{ static_cast<int>(l.size()) }; n >= 2 && CCW(l[n - 2], l[n - 1], s[i]) != CLOCKWISE; --n) {
			l.pop_back();
		}
		l.emplace_back(s[i]);
	}

	// 시계 방향에 있을 수 있게 볼록 껍질 점 배열 생성
	// 왜 시작 인덱스가 u.size() - 2 인가? => 마지막 하나의 원소는 이미 l에 포함되어 있기 때문
	// 왜 i를 1까지 하는가? => 마찬가지로 시작 원소 또한 이미 l에 포함되어 있기 때문
	reverse(begin(l), end(l));
	for (int i{ static_cast<int>(u.size()) - 2 }; i >= 1; --i) { 
		l.emplace_back(u[i]);
	}
	return l;
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	int N{}; cin >> N;
	vector<Point> points(N, Point(0,0));
	for (Point& p : points) {
		cin >> p.x >> p.y;
	}

	Polygon poly = move(AndrewScan(points));

	double sum{};
	Point stdP(move(poly[0]));
	N = static_cast<int>(poly.size());
	for (int i{ 1 }; i < N - 1; ++i) {
		Vector v1 = poly[i] - stdP;
		Vector v2 = poly[i + 1] - stdP;
		sum += static_cast<double>(Cross(v1, v2)) / 2; // 평행사변형 넓이 합
	}
	if (sum < 0) sum = -sum;
	sum /= 50; // 소 마리수
	cout << static_cast<ll>(sum) << '\n';

	return 0;
}