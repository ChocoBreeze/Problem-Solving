#include<iostream>
using std::cin;
using std::cout;
int main() {
	cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	int T;
	cin >> T;
	for (int i = 0; i < T; ++i) {
		int cnt = 0, x1, y1, x2, y2, n;
		cin >> x1 >> y1 >> x2 >> y2;
		cin >> n;
		for (int j = 0; j < n; ++j) {
			int cx, cy, r;
			cin >> cx >> cy >> r;
			// 출발이랑 도착이 모두 다 안에 있는 경우는 경계를 넘나들 필요가 없음.
			if ((cx - x1) * (cx - x1) + (cy - y1) * (cy - y1) < r * r && (cx - x2) * (cx - x2) + (cy - y2) * (cy - y2) < r * r) continue;
			if ((cx - x1) * (cx - x1) + (cy - y1) * (cy - y1) < r * r || (cx - x2) * (cx - x2) + (cy - y2) * (cy - y2) < r * r) ++cnt;
		}
		cout << cnt << "\n";
	}
	return 0;
}