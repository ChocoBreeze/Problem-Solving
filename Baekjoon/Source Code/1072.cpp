// X : 1 ~ 1,000,000,000 (10억), Y
// 게임을 몇 번 더 해야 승률이 변하는지
#include <iostream>
#include <algorithm>

using namespace std;
int X, Y;

auto cal_win_rate = [](long long X, long long Y) -> int {
	return Y * 100 / X; // 100을 먼저 곱하기(double로 바꿔서.. 했음..)
};

// 처음으로 승률이 Z보다 큰 값 찾기 -> upper_bound
long long u_bound(long long s, long long e, int Z) {
	while (s < e) {
		long long mid = s + (e - s) / 2;
		int win_rate = cal_win_rate(X + mid, Y + mid);
		if (s == 26927287424) {
			cout << "";
		}
		if (win_rate <= Z) s = mid + 1;
		else e = mid;
	}
	return s;
}


int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	int Z;
	cin >> X >> Y;
	Z = cal_win_rate(X, Y);
	long long answer = u_bound(1, 100000000000, Z);
	if (answer == 100000000000) cout << -1; // Z = 99 or Z = 98
	else cout << answer << "\n";
	return 0;
}