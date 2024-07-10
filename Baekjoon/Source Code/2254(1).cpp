/*
Graham's Scan �̿�
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

using namespace std;
using ll = long long;
constinit const int INITIALV = 10;

struct Point {
	int x, y;
	Point(int x, int y) : x(x), y(y) {}
	Point operator-(const Point& other) const;
	bool operator<(const Point& p) const { // y�� �켱���� y�� ������ x ��
		return y != p.y ? y < p.y : x < p.x;
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
	Point jail(0, 0);
	cin >> jail.x >> jail.y;
	Polygon points(N, Point(0, 0));
	for (Point& p : points) {
		cin >> p.x >> p.y;
	}

	// ù° �ٿ� �ִ� �� ���� ����Ѵ�. -> ���� �ٰ��� ���ʴ�� ���ϱ�(���� �ٱ�)
	int answer{};
	while (1) {
		if (points.size() < 3) break; // �ٰ��� ���� �� ����.

		sort(begin(points), end(points)); // ������ y��ǥ->x��ǥ ������ ����
		Point stdP(points[0].x, points[0].y); // ������

		// ������ ���� �ݽð� ���� ����
		sort(begin(points) + 1, end(points), [&stdP](const Point& p1, const Point& p2) {
			Point tempP1(p1.x - stdP.x, p1.y - stdP.y);
			Point tempP2(p2.x - stdP.x, p2.y - stdP.y);
			if (1LL * tempP1.y * tempP2.x != 1LL * tempP1.x * tempP2.y) return 1LL * tempP1.y * tempP2.x < 1LL * tempP1.x * tempP2.y; // �ݽð��� �� true
			return p1.y != p2.y ? p1.y < p2.y : p1.x < p2.x;
		});

		// stack<int> S; // stack ��� vector ���
		vector<int> poly;
		// ���ÿ� ó�� 2���� ���� ����
		poly.push_back(0);
		poly.push_back(1);

		int next{ 2 };
		N = static_cast<int>(points.size());
		while (next < N) { // ��� �� �ȱ�
			// ���ÿ� 2�� �̻��� ���� ���� �ִ� ��...
			while (poly.size() >= 2) {
				int first = poly.back(); poly.pop_back();
				int second = poly.back();
				// ���� �ֻ�� �� 2���� ���� ���� ���谡 CCW�� ������ ���� pop
				if (CCW(points[second], points[first], points[next]) == COUNTER_CLOCKWISE) {
					poly.push_back(first);
					break;
				}
			}
			// ���� ���� ���ÿ� �ֱ�
			poly.push_back(next++);
		}
		// ���ÿ� ������ ���� �����ϴ� �������� ������� �׿� ����.
		if (poly.size() < 3) break; // �ٰ����� �ƴ�

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

		poly.pop_back(); // ������ �ٽ� ���� ����
		// sort(begin(poly), end(poly)); // �������� ���� (���⼭�� ����������)

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