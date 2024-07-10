// Andrew Scan
// ���� �ε����� ������ �̾ƾ� �ؼ� ���� ��������..
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
	bool operator<(const Point& p) const { // x�� �켱���� x�� ������ y ��
		return x != p.x ? x < p.x : y < p.y;
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

bool AndrewScan(vector<int>& answer, vector<PointWithIndex>& s,int floor) {
	if (s.size() < 3) {
		return false;
	}
	Polygon u, l;
	vector<PointWithIndex> uWithIndex, lWithIndex;

	vector<PointWithIndex> sCopy(s); // ���� ������ �ʿ� ����.
	sort(begin(sCopy), end(sCopy));
	// x�� ���� �ͺ��� 2���� u�� �߰�
	u.emplace_back(sCopy[0].p);
	u.emplace_back(sCopy[1].p);
	uWithIndex.emplace_back(sCopy[0].p.x, sCopy[0].p.y, sCopy[0].index);
	uWithIndex.emplace_back(sCopy[1].p.x, sCopy[1].p.y, sCopy[1].index);

	// x�� ū �ͺ��� 2���� l�� �߰�
	int last = static_cast<int>(s.size());
	l.emplace_back(sCopy[last - 1].p);
	l.emplace_back(sCopy[last - 2].p);
	lWithIndex.emplace_back(sCopy[last - 1].p.x, sCopy[last - 1].p.y, sCopy[last - 1].index);
	lWithIndex.emplace_back(sCopy[last - 2].p.x, sCopy[last - 2].p.y, sCopy[last - 2].index);

	// ���� ���� �� �κ� �����
	for (int i{ 2 }; i < last; ++i) {
		// �ٰ����� �� ���� �� -> ������
		for (int n{ static_cast<int>(u.size()) }; n >= 2 && CCW(u[n - 2], u[n - 1], sCopy[i].p) != CLOCKWISE; --n) {
			u.pop_back();
			uWithIndex.pop_back();
		}
		u.emplace_back(sCopy[i].p);
		uWithIndex.emplace_back(sCopy[i].p.x, sCopy[i].p.y, sCopy[i].index);
	}

	// ���� ���� �Ʒ� �κ� �����
	for (int i{ static_cast<int>(s.size()) - 3 }; i >= 0; --i) {
		// �ٰ����� �� ���� �� -> ������
		for (int n{ static_cast<int>(l.size()) }; n >= 2 && CCW(l[n - 2], l[n - 1], sCopy[i].p) != CLOCKWISE; --n) {
			l.pop_back();
			lWithIndex.pop_back();
		}
		l.emplace_back(sCopy[i].p);
		lWithIndex.emplace_back(sCopy[i].p.x, sCopy[i].p.y, sCopy[i].index);
	}

	// �ð� ���⿡ ���� �� �ְ� ���� ���� �� �迭 ����
	// �� ���� �ε����� u.size() - 2 �ΰ�? => ������ �ϳ��� ���Ҵ� �̹� l�� ���ԵǾ� �ֱ� ����
	// �� i�� 1���� �ϴ°�? => ���������� ���� ���� ���� �̹� l�� ���ԵǾ� �ֱ� ����
	reverse(begin(l), end(l));
	for (int i{ static_cast<int>(u.size()) - 2 }; i >= 1; --i) {
		l.emplace_back(u[i]);
		lWithIndex.emplace_back(uWithIndex[i]);
	}

	if (static_cast<int>(lWithIndex.size()) < 3) return false; // �ٰ��� ���� �� ����.

	sort(begin(lWithIndex), end(lWithIndex), [](const PointWithIndex& pi1, const PointWithIndex& pi2) {
		return pi1.index < pi2.index;
	});
	vector<PointWithIndex> sTemp;
	sTemp.swap(s);
	int index{};
	for (int i{}; i < static_cast<int>(sTemp.size()); ++i) {
		if (index < static_cast<int>(lWithIndex.size()) && lWithIndex[index].index == sTemp[i].index) {
			answer[lWithIndex[index].index] = floor;
			++index;
			continue;
		}
		s.emplace_back(sTemp[i]);
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
		if (!AndrewScan(answer, points, floor)) break;
	}

	for (int& a : answer) {
		cout << a << ' ';
	}
	cout << '\n';

	return 0;
}