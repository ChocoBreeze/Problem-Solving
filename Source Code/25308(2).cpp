// Graham's Scan
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

Polygon GrahamScan(Polygon& s) {
	Polygon poly;
	if (s.size() < 3) return poly; // return empty vector

	sort(begin(s), end(s));
	Point stdP(s[0].x, s[0].y);

	// 기준점 빼고 반시계 정렬
	sort(begin(s) + 1, end(s), [&stdP](const Point& p1, const Point& p2) {
		Point tempP1(p1.x - stdP.x, p1.y - stdP.y);
		Point tempP2(p2.x - stdP.x, p2.y - stdP.y);
		if (1LL * tempP1.y * tempP2.x != 1LL * tempP1.x * tempP2.y) return 1LL * tempP1.y * tempP2.x < 1LL * tempP1.x * tempP2.y; // 반시계일 때 true
		return p1.y != p2.y ? p1.y < p2.y : p1.x < p2.x;
		});

	poly.emplace_back(s[0].x, s[0].y);
	poly.emplace_back(s[1].x, s[1].y);

	int next{ 2 };
	int N = static_cast<int>(s.size());
	while (next < N) { // 모든 점 훑기
		// 스택에 2개 이상의 점이 남아 있는 한...
		while (poly.size() >= 2) {
			Point first = *(poly.end() - 1);
			Point second = *(poly.end() - 2);
			// 스택 최상단 점 2개와 다음 점의 관계가 CCW일 때까지 스택 pop
			if (CCW(second, first, s[next]) == COUNTER_CLOCKWISE) {
				break;
			}
			poly.pop_back();
		}
		// 다음 점을 스택에 넣기
		poly.emplace_back(s[next].x, s[next].y);
		++next;
	}

	if (static_cast<int>(poly.size()) < 3) return Polygon(); // 추가 - empty vector

	return poly;
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

		Polygon poly(move(GrahamScan(points)));
		if (poly.size() == SIZE) ++answer;
	} while (next_permutation(begin(indeces), end(indeces)));

	cout << answer << '\n';
	return 0;
}