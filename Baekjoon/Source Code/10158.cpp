// 처음엔 노가다로 했음.(시간 초과)
// https://www.acmicpc.net/board/view/66730
// 생각해보니 그렇다..
#include<iostream>

using namespace std;

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	int w, h;
	cin >> w >> h;
	int x, y, t;
	cin >> x >> y >> t;

	// 시작 방향이 정해져있으니 이렇게 가능한듯.
	// 방향에 따라 조정해주면 간편할듯!
	if (((x + t) / w) % 2 == 0) { // 튕긴 횟수
		x = (x + t) % w;
	}
	else {
		x = w - ((x + t) % w);
	}
	if (((y + t) / h) % 2 == 0) { // 튕긴 횟수
		y = (y + t) % h;
	}
	else {
		y = h - ((y + t) % h);
	}

	cout << x << " " << y;

	return 0;
}