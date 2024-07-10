/*
공평하게 X개 -> K명이면 K * X 개
한 명은 잃어 버림 -> K*X + 1개
한 봉지에는 사탕이 C개 있음.
최대 구매 가능한 사탕 봉지는 10^9 = 10억
확장 유클리도 호제법!
음수 해가 나오는 경우 어떻게 할지 몰라 당황했음..
*/
#include<iostream>

using namespace std;

int GCD(int K, int C) {
	if (!C) return K;
	else return GCD(C, K % C);
}

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	int T, K, C;
	cin >> T;
	for (int i = 0; i < T; ++i) {
		cin >> K >> C;
		// K*X = C*A - 1인 가장 작은 A 구하기
		// GCD(C,K) = 1 당연하니 검사할 필요 없다!
		// 하지만 GCD(C, K) != 1인 경우에 impossible이다!
		if (GCD(K, C) != 1) {
			cout << "IMPOSSIBLE\n";
			continue;
		}
		if (K == 1 && C == 1) { // 따로 처리?
			cout << "2\n"; 
			continue;
		}
		// C*A - K*X = 1인 정수 쌍(A,X) 찾기 
		// K : 명수 - t, A : 사야 할 사탕 수 - s
		// C*A + K*X = 1을 solve (t < 0 && s > 0)이도록
		long long s1 = 1, s2 = 0, t1 = 0, t2 = 1;
		long long r1 = C, r2 = K, q = 0;
		while (r2!=1) {
			long long r, q, s, t;
			r = r1 % r2;
			q = r1 / r2;
			s = s1 - q * s2;
			t = t1 - q * t2;
			s1 = s2; s2 = s;
			t1 = t2; t2 = t;
			r1 = r2; r2 = r;
		}
		while (s2 <= 0 || t2 >= 0) { // 음수해인 경우에 당황했음!(어떻게 할지 몰라서)
			s2 += K;
			t2 -= C;
		}
		if (s2 > 1000000000) cout << "IMPOSSIBLE\n";
		else cout << s2 << "\n";
	}

	return 0;
}
