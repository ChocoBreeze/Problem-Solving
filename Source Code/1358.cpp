#include<iostream>

using std::cout;
using std::cin;

int main() {
	cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	int W, H, X, Y, P, x, y, chk = 0, answer = 0;
	cin >> W >> H >> X >> Y >> P;
	int radius = H / 2; // H는 짝수만
	for (int i = 0; i < P; ++i) {
		cin >> x >> y;
		chk = 0;
		// rectangle
		if ((x>=X && x<=X+W) && (y>=Y && y<=Y+H)) chk=1;
		// left circle
		if ((x - X) * (x - X) + (y - Y - radius) * (y - Y - radius) <= radius * radius) chk = 1;
		// right circle
		if ((x - X - W) * (x - X - W) + (y - Y - radius) * (y - Y - radius) <= radius * radius) chk = 1;
		//링크 안이면 누적
		if (chk == 1) ++answer;
	}
	cout << answer;

	return 0;
}