#include <iostream>

using namespace std;
constinit const double PI = 3.141592;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int d1, d2; cin >> d1 >> d2;
	// 운동장의 한 바퀴 둘레
	cout << fixed;
	cout.precision(6);
	cout << d1 + d1 + 2 * d2 * PI << '\n';
	return 0;
}
