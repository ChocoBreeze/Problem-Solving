#include <iostream>
#include <cmath>

using namespace std;
// 아이디어
// https://blog.naver.com/PostView.naver?blogId=kks227&logNo=220610580318
// 신박하네..

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int X, Y, D, T; cin >> X >> Y >> D >> T;
	// (X, Y) -> (0, 0)
	// 점프 : T초에 D만큼 움직이기

	double dist = sqrt(X * X + Y * Y);
	double answer{};
	if (dist < D) {
		// 더 멀리 점프 후 걷기 (
		double jumpAndWalk = T + (D - dist);
		// 그냥 걷기
		double walk{ dist };
		// 두 번 뛰기
		double twoJump = 2 * T;
		answer = min({ jumpAndWalk, walk, twoJump });
	}
	else { // dist >= D
		// 2번 이상 점프해야 함. => 무조건 딱 맞게 갈 수 있음.
		// 그냥 걷기
		double walk{ dist };
		int minJump = static_cast<int>(dist / D);
		// only jump - (minJump + 1)번
		double jump = T * (minJump + 1);
		// jump(minJump) 후 남은 거리 걷기
		double jumpAndWalk = T * minJump + (dist - (D * minJump));
		answer = min({ walk, jump, jumpAndWalk });
	}

	cout << fixed;
	cout.precision(10);
	cout << answer << '\n';
	return 0;
}
