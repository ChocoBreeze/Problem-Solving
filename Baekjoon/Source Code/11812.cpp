#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
// root node를 0번으로 설정

int main() {
	cin.tie(NULL)->sync_with_stdio(false); // 한 줄에!
	long long N, K, Q, a, b;
	cin >> N >> K >> Q;
	// 10^15 ~ 2^50; -> sparse table 다 만들기엔 크다
	for (int q = 0; q < Q; ++q) {
		cin >> a >> b;
		a--;
		b--;
		long long answer = 0; // int로 감당 x
		if (K == 1) { // TLE 73%
			answer = abs(a - b);
		}
		else {
			long long a_height = -1, b_height = -1;
			long long start = 0, end = 0, height = 0;
			long long nom = 1;
			while (a_height == -1 || b_height == -1) {
				if (a_height == -1 && a >= start && a <= end) a_height = height;
				if (b_height == -1 && b >= start && b <= end) b_height = height;
				height++;
				start = end + 1;
				nom *= K;
				end += nom;
			}
			if (a_height > b_height) { // b_height가 크도록
				swap(a, b);
				swap(a_height, b_height);
			}
			while (a_height != b_height) {
				b_height--;
				b = (b - 1) / K;
				answer++;
			}
			while (a != b) {
				b = (b - 1) / K;
				a = (a - 1) / K;
				answer += 2;
			}
		}
		cout << answer << "\n";
	}
	return 0;
}