// 시간
#include<iostream>

using namespace std;

int gcd(int x, int y) {
	if (y == 0) return x;
	else return gcd(y, x % y);
}

int find_year(int year_plus, int start_year, int other_year_cal, int other_year, int limit) {
	int answer = -1;
	for (int year = start_year;; year += year_plus) {
		int other_ = year % other_year_cal == 0 ? other_year_cal : year % other_year_cal;
		if (other_ == other_year) {
			answer = year;
			break;
		}
		if (year > limit) break; // 종말
	}
	return answer;
}

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	int T;
	cin >> T;
	int M, N, x, y;
	for (int t = 0; t < T; ++t) {
		cin >> M >> N >> x >> y;
		int gcd_M_N = gcd(M, N);
		int lcm_M_N = M * (N / gcd_M_N);
		int answer;
		if (M > N) answer = find_year(M, x, N, y, lcm_M_N);
		else answer = find_year(N, y, M, x, lcm_M_N);
		cout << answer<<"\n";
	}
	return 0;
}