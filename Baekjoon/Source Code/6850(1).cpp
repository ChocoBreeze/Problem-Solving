/*
Graham's Scan
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

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	int N{}; cin >> N;
	vector<Point> points(N, Point(0,0));
	for (Point& p : points) {
		cin >> p.x >> p.y;
	}

	sort(begin(points), end(points)); // 가장 왼쪽 아래 점 찾기 위해서 정렬
	Point stdP(points[0].x, points[0].y); // 기준점

	auto compare = [&stdP](const Point& p1, const Point& p2) {
		Point tempP1(p1.x - stdP.x, p1.y - stdP.y);
		Point tempP2(p2.x - stdP.x, p2.y - stdP.y);
		if (1LL * tempP1.y * tempP2.x != 1LL * tempP1.x * tempP2.y) { // 반시계일 때 true
			return 1LL * tempP1.y * tempP2.x < 1LL * tempP1.x * tempP2.y;
		}
		return p1.y != p2.y ? p1.y < p2.y : p1.x < p2.x; // 기존 크기 비교
	};
	sort(begin(points) + 1, end(points), compare); // 기준점에서 반시계 방향 정렬

	// stack 대신 vector 사용
	vector<int> poly;
	poly.push_back(0);
	poly.push_back(1);

	int next{ 2 };
	N = static_cast<int>(points.size());
	while (next < N) { // 모든 점 훑기
		while (poly.size() >= 2) { // 스택에 2개 이상의 점이 남아 있는 한
			int first = *(poly.end() - 1); // poly.back()
			int second = *(poly.end() - 2);
			// 스택 최상단 점 2개와 다음 절의 관계가 CCW일 때까지 스택 pop
			if (CCW(points[second], points[first], points[next]) == COUNTER_CLOCKWISE) {
				break;
			}
			poly.pop_back();
		}
		poly.push_back(next++); // 다음 점을 스택에 넣기
	}

	ll sum{};
	stdP = points[poly[0]];
	N = static_cast<int>(poly.size());
	for (int i{ 1 }; i < N - 1; ++i) {
		// poly를 계산에 사용해야 하는데, 다른 점 넣어놓고 뭐가 틀린지 찾고 있네..
		Vector v1 = points[poly[i]] - stdP;
		Vector v2 = points[poly[i + 1]] - stdP;
		sum += Cross(v1, v2) / 2; // 평행사변형 넓이 합
	}
	if (sum < 0) sum = -sum;
	sum /= 50; // 소 마리수
	cout << sum << '\n';

	return 0;
}