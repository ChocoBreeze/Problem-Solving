// Graham Scan
// 원래 인덱스를 답으로 뽑아야 해서 조금 더러워진..
#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>

using namespace std;
using ll = long long;

struct Point {
	int x, y;
	Point(int x, int y) : x(x), y(y) {}
	Point operator-(const Point& other) const;
	bool operator<(const Point& p) const { // x를 우선으로 x가 같으면 y 비교
		return y != p.y ? y < p.y : x < p.x;
	}
};
using Vector = Point;
using Polygon = vector<Point>;
struct PointWithIndex {
	Point p;
	int index;
	PointWithIndex(int x, int y, int index) : p(x, y), index(index) {}
	bool operator<(const PointWithIndex& other) const { 
		return p < other.p;
	}
};

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

bool GrahamScan(vector<int>& answer, vector<PointWithIndex>& s, int floor) {
	if (s.size() < 3) return false;

	vector<PointWithIndex> sCopy(s);
	sort(begin(s), end(s));
	PointWithIndex stdP(s[0].p.x, s[0].p.y, s[0].index);

	// 기준점 빼고 반시계 정렬
	sort(begin(s) + 1, end(s), [&stdP](const PointWithIndex& pi1, const PointWithIndex& pi2) {
		Point tempP1(pi1.p.x - stdP.p.x, pi1.p.y - stdP.p.y);
		Point tempP2(pi2.p.x - stdP.p.x, pi2.p.y - stdP.p.y);
		if (1LL * tempP1.y * tempP2.x != 1LL * tempP1.x * tempP2.y) return 1LL * tempP1.y * tempP2.x < 1LL * tempP1.x * tempP2.y; // 반시계일 때 true
		return pi1.p < pi2.p;
	});

	vector<int> poly;
	poly.push_back(0);
	poly.push_back(1);

	int next{ 2 };
	int N = static_cast<int>(s.size());
	while (next < N) { // 모든 점 훑기
		// 스택에 2개 이상의 점이 남아 있는 한...
		while (poly.size() >= 2) {
			int first = *(poly.end() - 1);
			int second = *(poly.end() - 2);
			// 스택 최상단 점 2개와 다음 점의 관계가 CCW일 때까지 스택 pop
			if (CCW(s[second].p, s[first].p, s[next].p) == COUNTER_CLOCKWISE) {
				break;
			}
			poly.pop_back();
		}
		// 다음 점을 스택에 넣기
		poly.push_back(next++);
	}

	if (static_cast<int>(poly.size()) < 3) return false; // 추가

	vector<int> idx;
	for (int& po : poly) {
		answer[s[po].index] = floor;
		idx.push_back(s[po].index);
	}

	sort(begin(idx), end(idx));
	int index{};
	vector<PointWithIndex>().swap(s); // swap with empty vector
	for (int i{}; i < static_cast<int>(sCopy.size()); ++i) {
		if (index < static_cast<int>(idx.size()) && idx[index] == sCopy[i].index) {
			++index;
			continue;
		}
		s.emplace_back(sCopy[i]);
	}
	return true;
}

int main() {
	cin.tie(nullptr), ios::sync_with_stdio(false);
	int n{}; cin >> n;
	// Polygon points(n, Point(0,0));
	vector<PointWithIndex> points(n, PointWithIndex(0, 0, 0));
	int index{};
	for (PointWithIndex& p : points) {
		cin >> p.p.x >> p.p.y;
		p.index = index++;
	}
	vector<int> answer(n, 0); // non-use = 0
	for (int floor{ 1 };; ++floor) {
		if (!GrahamScan(answer, points, floor)) break;
	}

	for (int& a : answer) {
		cout << a << ' ';
	}
	cout << '\n';

	return 0;
}