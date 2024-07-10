/*
Andrew's Scan �̿�
���̵�� : https://m.blog.naver.com/kks227/220857597424
1. ���� ������ ����
2. ������ ���� ���� �ȿ� ������ ���ԵǴ��� Ȯ��(��ġ�� �� ��)
	���Ե��� ������ ����
3. ������ ���� ������ ���Եȴٸ�
	���� 1�߰�(�� �� �߰�)
	���� ������ ���� ���� ���� �� �ٽ� 1�� ���� ����
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>

using namespace std;
using ll = long long;
constinit const int INITIALV = 10;

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

Point Point::operator-(const Point& other) const
{
	return Point(this->x - other.x, this->y - other.y);
}

ll Dot(const Vector& v1, const Vector& v2) {
	return 1LL * v1.x * v2.x + 1LL * v1.y * v2.y;
}
ll Cross(const Vector& v1, const Vector& v2) {
	return 1LL* v1.x * v2.y - 1LL * v1.y * v2.x;
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

vector<int> AndrewScan(Polygon& s) { // index�� �����ϵ��� ����
	if (s.size() < 3) {
		vector<int> ret;
		const int SIZE = static_cast<int>(s.size());
		for (int v : std::views::iota(0) | std::views::take(SIZE)) ret.push_back(v); // ?
		return ret;
	}
	Polygon u, l;
	vector<int> uIndex, lIndex;

	sort(begin(s), end(s));
	// x�� ���� �ͺ��� 2���� u�� �߰�
	uIndex.push_back(0);
	uIndex.push_back(1);
	u.emplace_back(s[0]);
	u.emplace_back(s[1]);

	// x�� ū �ͺ��� 2���� l�� �߰�
	int last = static_cast<int>(s.size());
	lIndex.push_back(last - 1);
	lIndex.push_back(last - 2);
	l.emplace_back(s[last - 1]);
	l.emplace_back(s[last - 2]);

	// ���� ���� �� �κ� �����
	for (int i{ 2 }; i < last; ++i) {
		// ������ �� ��� �� ��� �� ���� �������� ���� �ʴ�. => ������ ���鸸 pop
		for (int n{ static_cast<int>(u.size()) }; n >= 2 && CCW(u[n - 2], u[n - 1], s[i]) == COUNTER_CLOCKWISE; --n) {
			u.pop_back();
			uIndex.pop_back();
		}
		u.emplace_back(s[i]);
		uIndex.push_back(i);
	}

	// ���� ���� �Ʒ� �κ� �����
	for (int i{ static_cast<int>(s.size()) - 3 }; i >= 0; --i) {
		// ������ �� ��� �� ��� �� ���� �������� ���� �ʴ�. => ������ ���鸸 pop
		for (int n{ static_cast<int>(l.size()) }; n >= 2 && CCW(l[n - 2], l[n - 1], s[i]) == COUNTER_CLOCKWISE; --n) {
			l.pop_back();
			lIndex.pop_back();
		}
		l.emplace_back(s[i]);
		lIndex.push_back(i);
	}

	// �ð� ���⿡ ���� �� �ְ� ���� ���� �� �迭 ����
	// �� ���� �ε����� u.size() - 2 �ΰ�? => ������ �ϳ��� ���Ҵ� �̹� l�� ���ԵǾ� �ֱ� ����
	// �� i�� 1���� �ϴ°�? => ���������� ���� ���� ���� �̹� l�� ���ԵǾ� �ֱ� ����
	reverse(begin(l), end(l));
	reverse(begin(lIndex), end(lIndex));
	for (int i{ static_cast<int>(u.size()) - 2 }; i >= 1; --i) {
		l.emplace_back(u[i]);
		lIndex.push_back(uIndex[i]);
	}
	// return l;
	return lIndex;
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	int N{}; cin >> N;
	Point jail(0,0);
	cin >> jail.x >> jail.y;
	Polygon points(N, Point(0, 0));
	for (Point& p : points) {
		cin >> p.x >> p.y;
	}

	// ù° �ٿ� �ִ� �� ���� ����Ѵ�. -> ���� �ٰ��� ���ʴ�� ���ϱ�(���� �ٱ�)
	int answer{};
	while (1) {
		vector<int> poly(move(AndrewScan(points)));

		if (poly.size() < 3) break; // �ٰ��� X

		poly.push_back(poly[0]); // ������ �� �� �� �߰�
		// ���� ���� �ٰ����� ������ �����ϴ��� Ȯ��
		/*
			�Ǻ��ϰ� ���� ���� O�� ��, ���ϴٰ��� ���� ��� ���ӵ� �� �� P, Q�� ����
			���� OP�� ���� OQ�� CW/CCW ���ΰ� ���� ������ �� O�� ���ϴٰ��� ���ο�, �ƴ϶�� �ܺο� ����.
		*/
		bool isContain{ true };
		int last{ INITIALV };
		
		for (int now{ 0 }; now < static_cast<int>(poly.size()) - 1; ++now) {
			Point& p1 = points[poly[now]];
			Point& p2 = points[poly[now + 1]];

			int curr = CCW(jail, p1, p2);
			if (last == INITIALV) last = curr;
			else {
				if (last != curr) {
					isContain = false;
					break;
				}
			}
		}

		// ���� �� �ϸ� ��.
		if (!isContain) break;

		// ��, ���� �ٸ� �� ���� �ϳ��� �㺭���̳� �� ����� �����ؼ��� �� �ȴ�.
		// �� �� �� �� �߰� �� ������ ���� ���� ����
		
		// poly�� ����� ������ index�� �����Ǵ� ������ �ƴ�..!!!
		poly.pop_back(); // ������ �ٽ� ���� ����
		sort(begin(poly), end(poly)); // �������� ����

		++answer;
		Polygon tempPoints;
		int index{};
		for (int i{}; i < static_cast<int>(points.size()); ++i) {
			if (index < static_cast<int>(poly.size()) && i == poly[index]) {
				index++;
				continue;
			}
			tempPoints.emplace_back(points[i]);
		}
		points.swap(tempPoints);
	}
	cout << answer << '\n';
	return 0;
}