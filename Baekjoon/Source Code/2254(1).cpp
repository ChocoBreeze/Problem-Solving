/*
Graham's Scan 이용
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

using namespace std;
using ll = long long;
constinit const int INITIALV = 10;

struct Point {
	int x, y;
	Point(int x, int y) : x(x), y(y) {}
	Point operator-(const Point& other) const;
	bool operator<(const Point& p) const { // y를 우선으로 y가 같으면 x 비교
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

	// 첫째 줄에 최대 겹 수를 출력한다. -> 볼록 다각형 차례대로 구하기(가장 바깥)
	int answer{};
	while (1) {
		if (points.size() < 3) break; // 다각형 만들 수 없음.

		sort(begin(points), end(points)); // 점들을 y좌표->x좌표 순으로 정렬
		Point stdP(points[0].x, points[0].y); // 기준점

		// 기준점 빼고 반시계 방향 정렬
		sort(begin(points) + 1, end(points), [&stdP](const Point& p1, const Point& p2) {
			Point tempP1(p1.x - stdP.x, p1.y - stdP.y);
			Point tempP2(p2.x - stdP.x, p2.y - stdP.y);
			if (1LL * tempP1.y * tempP2.x != 1LL * tempP1.x * tempP2.y) return 1LL * tempP1.y * tempP2.x < 1LL * tempP1.x * tempP2.y; // 반시계일 때 true
			return p1.y != p2.y ? p1.y < p2.y : p1.x < p2.x;
		});

		// stack<int> S; // stack 대신 vector 사용
		vector<int> poly;
		// 스택에 처음 2개의 점을 넣음
		poly.push_back(0);
		poly.push_back(1);

		int next{ 2 };
		N = static_cast<int>(points.size());
		while (next < N) { // 모든 점 훑기
			// 스택에 2개 이상의 점이 남아 있는 한...
			while (poly.size() >= 2) {
				int first = poly.back(); poly.pop_back();
				int second = poly.back();
				// 스택 최상단 점 2개와 다음 점의 관계가 CCW일 때까지 스택 pop
				if (CCW(points[second], points[first], points[next]) == COUNTER_CLOCKWISE) {
					poly.push_back(first);
					break;
				}
			}
			// 다음 점을 스택에 넣기
			poly.push_back(next++);
		}
		// 스택에 컨벡스 헐을 구성하는 정점들이 순서대로 쌓여 있음.
		if (poly.size() < 3) break; // 다각형이 아님

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

		poly.pop_back(); // 시작점 다시 빼고 정렬
		// sort(begin(poly), end(poly)); // 오름차순 증가 (여기서는 오름차순임)

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