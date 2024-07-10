/*
Andrew's Scan 이용
아이디어 : https://m.blog.naver.com/kks227/220857597424
1. 볼록 껍질을 추출
2. 추출한 볼록 껍질 안에 감옥이 포함되는지 확인(겹치면 안 됨)
	포함되지 않으면 종료
3. 감옥이 볼록 껍질에 포함된다면
	답을 1추가(한 겹 추가)
	볼록 껍질에 사용된 점들 제외 후 다시 1번 과정 진행
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
	bool operator<(const Point& p) const { // x를 우선으로 x가 같으면 y 비교
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

vector<int> AndrewScan(Polygon& s) { // index만 저장하도록 변경
	if (s.size() < 3) {
		vector<int> ret;
		const int SIZE = static_cast<int>(s.size());
		for (int v : std::views::iota(0) | std::views::take(SIZE)) ret.push_back(v); // ?
		return ret;
	}
	Polygon u, l;
	vector<int> uIndex, lIndex;

	sort(begin(s), end(s));
	// x가 작은 것부터 2개를 u에 추가
	uIndex.push_back(0);
	uIndex.push_back(1);
	u.emplace_back(s[0]);
	u.emplace_back(s[1]);

	// x가 큰 것부터 2개를 l에 추가
	int last = static_cast<int>(s.size());
	lIndex.push_back(last - 1);
	lIndex.push_back(last - 2);
	l.emplace_back(s[last - 1]);
	l.emplace_back(s[last - 2]);

	// 볼록 껍질 윗 부분 만들기
	for (int i{ 2 }; i < last; ++i) {
		// 감옥과 담 기둥 중 어느 세 점도 일직선상에 있지 않다. => 오목인 점들만 pop
		for (int n{ static_cast<int>(u.size()) }; n >= 2 && CCW(u[n - 2], u[n - 1], s[i]) == COUNTER_CLOCKWISE; --n) {
			u.pop_back();
			uIndex.pop_back();
		}
		u.emplace_back(s[i]);
		uIndex.push_back(i);
	}

	// 볼록 껍질 아랫 부분 만들기
	for (int i{ static_cast<int>(s.size()) - 3 }; i >= 0; --i) {
		// 감옥과 담 기둥 중 어느 세 점도 일직선상에 있지 않다. => 오목인 점들만 pop
		for (int n{ static_cast<int>(l.size()) }; n >= 2 && CCW(l[n - 2], l[n - 1], s[i]) == COUNTER_CLOCKWISE; --n) {
			l.pop_back();
			lIndex.pop_back();
		}
		l.emplace_back(s[i]);
		lIndex.push_back(i);
	}

	// 시계 방향에 있을 수 있게 볼록 껍질 점 배열 생성
	// 왜 시작 인덱스가 u.size() - 2 인가? => 마지막 하나의 원소는 이미 l에 포함되어 있기 때문
	// 왜 i를 1까지 하는가? => 마찬가지로 시작 원소 또한 이미 l에 포함되어 있기 때문
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

	// 첫째 줄에 최대 겹 수를 출력한다. -> 볼록 다각형 차례대로 구하기(가장 바깥)
	int answer{};
	while (1) {
		vector<int> poly(move(AndrewScan(points)));

		if (poly.size() < 3) break; // 다각형 X

		poly.push_back(poly[0]); // 시작점 한 번 더 추가
		// 뽑은 볼록 다각형이 감옥을 포함하는지 확인
		/*
			판별하고 싶은 점이 O일 때, 볼록다각형 상의 모든 연속된 두 점 P, Q에 대해
			벡터 OP와 벡터 OQ의 CW/CCW 여부가 전부 같으면 점 O는 볼록다각형 내부에, 아니라면 외부에 있음.
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

		// 포함 안 하면 끝.
		if (!isContain) break;

		// 즉, 서로 다른 두 담이 하나의 담벼락이나 담 기둥을 공유해서는 안 된다.
		// 겹 수 한 개 추가 후 기존에 사용된 점들 제외
		
		// poly에 저장된 순서가 index가 증가되는 순서가 아님..!!!
		poly.pop_back(); // 시작점 다시 빼고 정렬
		sort(begin(poly), end(poly)); // 오름차순 증가

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