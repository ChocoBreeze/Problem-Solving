#include <iostream>
#include <cmath>
#include <algorithm>
#include <numbers>

using namespace std;
using namespace std::numbers; // pi_v

struct Circle {
	double x, y, r;
	Circle(double x, double y, double r) : x(x), y(y), r(r) {}
	Circle() = default;
};

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	Circle c1{}, c2{};
	cin >> c1.x >> c1.y >> c1.r >> c2.x >> c2.y >> c2.r;

	if (c1.r < c2.r) swap(c1, c2); // c1이 더 크도록

	double answer{};
	double dist = sqrt((c1.x - c2.x) * (c1.x - c2.x) + (c1.y - c2.y) * (c1.y - c2.y));

	if (dist >= c1.r + c2.r) answer = 0; // 겹치는 부분 없음
	else if (dist <= c1.r - c2.r) answer = pi_v<double> * c2.r * c2.r; // 안 쪽에서 겹침 - 작은 원 넓이
	else {
		// 코사인 제2법칙
		// r2 * r2 = r1 * r1 + d * d - 2 * r1 * d * cos(theta1)
		// 2 * r1 * d * cos(theta1) = r1 * r1 + d * d - r2 * r2
		// cos(theta1) = (r1 * r1 + d * d - r2 * r2) / (2 * r1 * d)
		auto theta1 = acos((c1.r * c1.r + dist * dist - c2.r * c2.r) / (2 * c1.r * dist));
		theta1 *= 2; // 구하고자 하는 각은 2배
		double s1 = 0.5 * c1.r * c1.r * theta1 - 0.5 * c1.r * c1.r * sin(theta1); // 부채꼴 - 삼각형
        
        // 반대편
		auto theta2 = acos((c2.r * c2.r + dist * dist - c1.r * c1.r) / (2 * c2.r * dist));
		theta2 *= 2;
		double s2 = 0.5 * c2.r * c2.r * theta2 - 0.5 * c2.r * c2.r * sin(theta2);
		
		answer = s1 + s2;
	}

	cout << fixed;
	cout.precision(3);
	cout << answer << '\n';

	return 0;
}