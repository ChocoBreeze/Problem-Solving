#include <iostream>
#include <vector>
#include <utility>

using namespace std;

struct Point {
	int x, y;
	Point(int x, int y) : x(x), y(y) {}
	Point(const Point& other) : x(other.x), y(other.y) {}
	Point operator+(const Point& other) const;
	Point operator-(const Point& other) const;
};
using Vector = Point;

Point Point::operator+(const Point& other) const {
	return Point(this->x + other.x, this->y + other.y);
}
Point Point::operator-(const Point& other) const {
	return Point(this->x - other.x, this->y - other.y);
}
int Dot(const Vector& a, const Vector& b) {
	return a.x * b.x + a.y * b.y;
}
int Cross(const Vector& a, const Vector& b) {
	return a.x * b.y - b.x * a.y;
}
int Norm(const Vector& a) {
	return a.x * a.x + a.y * a.y;
}

struct Segment {
	Point p1, p2;
	Segment(Point p1, Point p2) : p1(p1), p2(p2) {}
};

constinit const int ON_SEGMENT = 0; // p0 - p2 - p1
constinit const int CLOCKWISE = -1;
constinit const int COUNTER_CLOCKWISE = 1;
constinit const int ONLINE_FRONT = -2; // p0 - p1 - p2
constinit const int ONLINE_BACK = 2; // p2 - p0 - p1
int CCW(const Point& p0, const Point& p1, const Point& p2) {
	Vector a = p1 - p0;
	Vector b = p2 - p0;
	if (Cross(a, b) > 0) return COUNTER_CLOCKWISE;
	if (Cross(a, b) < 0) return CLOCKWISE;
	if (Dot(a, b) < 0) return ONLINE_BACK; // p2 - p0 - p1
	if (Norm(a) < Norm(b)) return ONLINE_FRONT; // p0 - p1 - p2

	return ON_SEGMENT; // p0 - p2 - p1
}

bool Intersect(const Point& p1, const Point& p2, const Point& p3, const Point& p4) {
	return(CCW(p1, p2, p3) * CCW(p1, p2, p4) <= 0 && CCW(p3, p4, p1) * CCW(p3, p4, p2) <= 0);
}

bool Intersect(const Segment& s1, const Segment& s2) {
	return Intersect(s1.p1, s1.p2, s2.p1, s2.p2);
}

struct UnionFind {
	vector<int> par;
	UnionFind(int n) : par(n, -1) {}

	int Find(int a) {
		if (par[a] < 0) return a;
		return par[a] = Find(par[a]);
	}

	bool Union(int a, int b) {
		a = Find(a), b = Find(b);
		if (a == b) return false;

		if (-par[a] < -par[b]) swap(a, b); // a 크기가 더 작은 경우 swap
		par[a] += par[b];
		par[b] = a;

		return true;
	}

	pair<int, int> GetAnswer() {
		vector<int> check(static_cast<int>(par.size()), 0);
		int groupCnt{}, maxSegment{-1};
		for (int i{}; i < static_cast<int>(par.size());++i) {
			int groupNum = Find(i);
			if (!check[groupNum]) {
				groupCnt++;
				check[groupNum] = 1;
				maxSegment = max(maxSegment, -par[groupNum]);
			}
		}
		return make_pair(groupCnt, maxSegment);
	}
};

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	int N{}; cin >> N;

	vector<Segment> segments(N, Segment(Point(0, 0), Point(0, 0)));
	for (Segment& s : segments) cin >> s.p1.x >> s.p1.y >> s.p2.x >> s.p2.y;

	// UnionFind + BruteForce
	UnionFind uf(N);
	for (int i1{}; i1 < N; ++i1) {
		for (int i2{ i1 + 1 }; i2 < N; ++i2) {
			if (Intersect(segments[i1], segments[i2])) {
				uf.Union(i1, i2);
			}
		}
	}

	pair<int, int> answer = uf.GetAnswer();
	cout << answer.first << '\n' << answer.second << '\n';
	return 0;
}